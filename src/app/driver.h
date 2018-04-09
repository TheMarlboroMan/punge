#ifndef APP_DRIVER
#define APP_DRIVER

#include <thread>
#include <chrono>

#include "display.h"

#include "../interpreter/parser.h"

namespace app {

class driver {

	public:

	void		run() {

		//TODO: Display constructor hides cursor, on destructor shows it again!
		
		try {
			display 	d;
			interpreter::parser 		p;
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

//TODO: This should be done by the display.	std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<"["<<curpos.x<<","<<curpos.y<<"]>>";
				d.refresh();

				std::this_thread::sleep_for(std::chrono::milliseconds(250));
				p.step();
			}

			//Exit cleanly...
//TODO: This should be done by the display too			std::cout<<tools::s::pos(exit_pos.x, exit_pos.y);
			std::flush(std::cout);
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


};

}

#endif
