#include "driver.h"

#include <thread>
#include <chrono>
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

		const int tick_speed=1000;
		const int refresh_rate=250; //Four times per second.

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;
		bool running=true;

		do_draw(d, p);

		while(running) {

			//TODO: interface for this, so we can swap to SDL or whatever.
			do_input(p.get_board());

			switch(state) {
				case states::edit:

				break;

				case states::play: {
				
					auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_tick);
					if(diff_tick.count() >= tick_speed) {
						last_tick=std::chrono::system_clock::now();
						p.step();
					}

					running=!p.is_end();
				}
				break;
			}

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

void driver::do_input(const interpreter::board& _board) {

	const auto indata=ti.get();

	if(indata) {

		if(tools::terminal_in_data::types::control==indata.type
		&& tools::terminal_in_data::controls::tab==indata.control) {
			
			state=state==states::play 
				? states::edit
				: states::play;
		}

		switch(state) {
			case states::play: do_input_play(_board, indata); break;
			case states::edit: do_input_edit(_board, indata); break;
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
}

void driver::do_draw(display& _d, const interpreter::parser& _parser) {

	switch(state) {
		case states::edit: do_draw_edit(_d, _parser); break;
		case states::play: do_draw_play(_d, _parser); break;
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
