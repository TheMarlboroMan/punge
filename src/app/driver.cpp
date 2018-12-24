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


		display 				d;
		interpreter::parser 	p;

//		p.load_board_from_filename("data/sets/original/test01.brd");
		p.new_board(20, 20);
		d.clear_terminal();

		const int tick_speed=1000;

		auto last_tick=std::chrono::system_clock::now();

		while(!p.is_end()) {

			do_input(p.get_board());

			const auto curpos=p.get_cursor().get_position();

			d.draw_board_borders(p.get_board());
			d.draw_board(p.get_board());

			//TODO: Change color when in string mode!!!
			//TODO: Set a reasonable refresh rate.
			d.draw_cursor(curpos, p.get_board());
			d.draw_edit_cursor(edit_cursor, p.get_board());
			d.draw_stack(p.get_stack());
			d.draw_output(p.get_output());
			d.draw_cursor_pos(curpos);
			d.refresh();
			auto diff=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-last_tick);

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
			if(_board.check_coords(future_position)) {
				edit_cursor=future_position;
			}
		}
	}
}
