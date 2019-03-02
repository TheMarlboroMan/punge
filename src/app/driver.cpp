#include "driver.h"

#include <thread>
#include <memory>
#include <iostream>

#include <terminal_out.h>

#include "terminal_display.h"
#include "drawing_routines.h"
#include "../interpreter/parser.h"


using namespace app;

void driver::run() {

	try {
		interpreter::parser 	p;

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);

		std::unique_ptr<display_interface> d(new terminal_display);
		d->clear();

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		do_draw(*d, p);

		while(states::exit!=state) {

			do_input(p.get_board());
			do_logic(p, last_tick);

			//TODO: Should not refresh until something has changed...
			auto diff_display=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_refresh);
			if(diff_display.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				do_draw(*d, p);
			}
		}

		//Exit cleanly...
		d->cleanup();
	}
	//TODO: This is actually a particular case of the
	//display initialization... should be another type of exception.
	catch(display_size_exception& e) {
		//TODO: Yeah, no...
		std::cout<<tools::s::text_color(tools::txt_red)
			<<tools::s::background_color(tools::bg_white)
			<<"You cannot play Punge in your terminal:"
			<<tools::s::reset_text()
			<<" "<<e.what()<<std::endl;
	}
	catch(...) {
		throw;
	}
}

void driver::do_logic(interpreter::parser& _p, t_time& _last_tick) {

	switch(state) {
		case states::edit:

		break;

		case states::play: {
	
			auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-_last_tick);
			if(diff_tick.count() >= tick_speed) {
				_last_tick=std::chrono::system_clock::now();
				_p.step();
			}

			if(_p.is_end()) {
				state=states::exit;
			}
		}
		break;
		case states::exit: 

		break;
	}
}


void driver::do_input(const interpreter::board& _board) {

	const auto indata=ti.get();

	if(indata) {

		if(tools::terminal_in_data::types::control==indata.type) {

			switch(indata.control) {
				case tools::terminal_in_data::controls::tab:
					state=state==states::play 
						? states::edit
						: states::play;
				break;
				case tools::terminal_in_data::controls::escape:
					state=states::exit;
				break;
				case tools::terminal_in_data::controls::enter:

				break;
				case tools::terminal_in_data::controls::backspace:

				break;
				case tools::terminal_in_data::controls::none:

				break;
			}
		}

		switch(state) {
			case states::play: do_input_play(_board, indata); break;
			case states::edit: do_input_edit(_board, indata); break;
			case states::exit: break;
		}
	}
}

void driver::do_input_play(const interpreter::board& /*_board*/, const tools::terminal_in_data&) {

}

void driver::do_input_edit(const interpreter::board& _board, const tools::terminal_in_data& _indata) {

	auto future_position=edit_cursor;

	if(tools::terminal_in_data::types::arrow==_indata.type) {
		switch(_indata.arrow) {
			case tools::terminal_in_data::arrowkeys::up: 		--future_position.y; break;
			case tools::terminal_in_data::arrowkeys::down:		++future_position.y; break;
			case tools::terminal_in_data::arrowkeys::left:		--future_position.x; break;
			case tools::terminal_in_data::arrowkeys::right:		++future_position.x; break;
			case tools::terminal_in_data::arrowkeys::none:		return;
		}

		//Validate the position...
		if(_board.check_coords(future_position)) {

			edit_cursor=future_position;
		}
	}
	else if(tools::terminal_in_data::types::chr==_indata.type) {

		//TODO: Search for a better solution?? Const casting is always a bad idea... 
		//The problem is how this method is called from another that gets a const board.
		const_cast<interpreter::board&>(_board).set_tile(edit_cursor, _indata.get_string_data()[0]);
	}
}

void driver::do_draw(display_interface& _di, const interpreter::parser& _parser) {

	switch(state) {
		case states::edit: do_draw_edit(_di, _parser); break;
		case states::play: do_draw_play(_di, _parser); break;
		case states::exit: break;
	}

	_di.refresh();
}

void driver::do_draw_edit(display_interface& _di, const interpreter::parser& _parser) {

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	draw_cursor(_di, edit_cursor, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::green);
	draw_cursor_pos(_di, edit_cursor); 
}

void driver::do_draw_play(display_interface& _di, const interpreter::parser& _parser) {

	const auto curpos=_parser.get_cursor().get_position();

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	draw_cursor(_di, curpos, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::red);
	draw_stack(_di, _parser.get_stack());
	draw_output(_di, _parser.get_output());
	draw_cursor_pos(_di, curpos);
}
