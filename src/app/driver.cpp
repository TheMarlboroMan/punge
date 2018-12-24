#include "driver.h"

#include <thread>
#include <chrono>
#include <iostream>

#include <terminal_in.h>
#include <terminal_out.h>

#include "display.h"

#include "../interpreter/parser.h"

using namespace app;

void driver::run() {

	try {

		tools::terminal_in 		ti;
		display 				d;
		interpreter::parser 	p;

		p.load_board_from_filename("data/sets/original/test01.brd");
		d.clear_terminal();

		while(!p.is_end()) {

			const auto curpos=p.get_cursor().get_position();

			d.draw_board_borders(p.get_board());
			d.draw_board(p.get_board());

			//TODO: Change color when in string mode!!!
			d.draw_cursor(curpos, p.get_board());
			d.draw_stack(p.get_stack());
			d.draw_output(p.get_output());
			d.draw_cursor_pos(curpos);
			d.refresh();

			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			p.step();
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
