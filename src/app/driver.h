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

		//TODO: Check terminal size!!!!!.
		//TODO: Exit if the terminal is too small.
		//TODO: Maybe save terminal size into the display???.
		//TODO: Maybe check all that shit into display???.

		//TODO: Display hides cursor, on destructor shows it again!
		display 	d;
		interpreter::coordinates 	board_pos{2,2};
		interpreter::coordinates 	borders_pos{1,1};
		interpreter::coordinates 	stack_pos{82, 1};
		interpreter::coordinates 	output_pos{1, 23};
		interpreter::coordinates 	input_pos{1, 24};
		interpreter::coordinates 	exit_pos{1, 25};

		interpreter::parser 		p;
		p.load_board_from_filename("data/sets/original/test01.brd");

		d.clear_terminal();

		while(!p.is_end()) {

			const auto curpos=p.get_cursor().get_position();

			d.draw_board_borders(borders_pos, p.get_board());
			d.draw_board(board_pos, p.get_board());
			//TODO: Change color when in string mode!!!
			d.draw_cursor(curpos, board_pos, p.get_board());
			d.draw_stack(stack_pos, p.get_stack());
			d.draw_output(output_pos, p.get_output());

			std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<"["<<curpos.x<<","<<curpos.y<<"]>>";
			d.refresh();

			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			p.step();
		}

		//Exit cleanly...
		std::cout<<tools::s::pos(exit_pos.x, exit_pos.y);
		std::flush(std::cout);
//		std::cin.clear();
//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}


};

}

#endif
