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

		//TODO: Should have the "edit" mode and the "run" mode.

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);

		display d;
		d.clear_terminal();

		const int tick_speed=1000;
		const int refresh_rate=250; //Four times per second.

		auto last_tick=std::chrono::system_clock::now();
		auto last_refresh=last_tick;

		do_draw(d, p);

		while(!p.is_end()) {

			do_input(p.get_board());
			auto diff=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_tick);

			if(diff.count() >= refresh_rate) {

				last_refresh=std::chrono::system_clock::now();
				do_draw(d, p);
			}

			if(diff.count() >= tick_speed) {

				last_tick=std::chrono::system_clock::now();
				p.step();
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

		auto future_position=edit_cursor;

		if(tools::terminal_in_data::types::arrow==indata.type) {
			switch(indata.arrow) {
				case tools::terminal_in_data::arrowkeys::up: 		--future_position.y; break;
				case tools::terminal_in_data::arrowkeys::down:		++future_position.y; break;
				case tools::terminal_in_data::arrowkeys::left:		--future_position.x; break;
				case tools::terminal_in_data::arrowkeys::right:		++future_position.x; break;
				case tools::terminal_in_data::arrowkeys::none:		return;
			}

			//Validate the position...
			//TODO: This is fucked up: I can go beyond the limits :/...
			//I guess we are not playing with the coordinate offsets correctly.
			if(_board.check_coords(future_position)) {
				edit_cursor=future_position;
			}
		}
	}
}

void driver::do_draw(display& _d, const interpreter::parser& _parser) {

	//TODO: Only if in run mode...
	const auto curpos=_parser.get_cursor().get_position();

	_d.draw_board_borders(_parser.get_board());
	_d.draw_board(_parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	_d.draw_cursor(curpos, _parser.get_board());
	_d.draw_edit_cursor(edit_cursor, _parser.get_board());
	_d.draw_stack(_parser.get_stack());
	_d.draw_output(_parser.get_output());
	_d.draw_cursor_pos(curpos);
	_d.refresh();
}
