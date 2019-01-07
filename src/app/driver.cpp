#include "driver.h"

#include <thread>
#include <iostream>

#include <terminal_out.h>

#include "display.h"

#include "../interpreter/parser.h"

using namespace app;

void driver::run() {

	try {
		interpreter::parser 	p;

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);

		display d;
		//TODO: Use an interface for this, so we can later swap shit.
		d.clear_terminal();


		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		do_draw(d, p);

		while(states::exit!=state) {

			do_input(p.get_board());
			do_logic(p, last_tick);

			//TODO: Should not refresh until something has changed...
			auto diff_display=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_refresh);
			if(diff_display.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				do_draw(d, p);
			}
		}

		//Exit cleanly...
		d.cleanup();
	}
	catch(display_size_exception& e) {
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

void driver::do_draw(display& _d, const interpreter::parser& _parser) {

	switch(state) {
		case states::edit: do_draw_edit(_d, _parser); break;
		case states::play: do_draw_play(_d, _parser); break;
		case states::exit: break;
	}

	_d.refresh();
}

void driver::do_draw_edit(display& _d, const interpreter::parser& _parser) {

	_d.draw_board_borders(_parser.get_board());
	_d.draw_board(_parser.get_board());

	_d.draw_cursor(edit_cursor, _parser.get_board(), tools::bg_green, tools::txt_white);
	_d.draw_cursor_pos(edit_cursor);
}

void driver::do_draw_play(display& _d, const interpreter::parser& _parser) {

	const auto curpos=_parser.get_cursor().get_position();

	//TODO: This is shit... we should actually try and make something better:
	//iterate for the board and game size and draw as needed, without printing
	//jumps here or there.

	_d.draw_board_borders(_parser.get_board());
	_d.draw_board(_parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	_d.draw_cursor(curpos, _parser.get_board(), tools::bg_red, tools::txt_white);
	_d.draw_stack(_parser.get_stack());
	_d.draw_output(_parser.get_output());
	_d.draw_cursor_pos(curpos);
}
