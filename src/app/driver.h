#ifndef APP_DRIVER
#define APP_DRIVER

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

		display 	d;
		interpreter::coordinates 	board_pos{2,2};
		interpreter::coordinates 	borders_pos{1,1};
		interpreter::coordinates 	input_pos{1, 23};
		interpreter::coordinates 	stack_pos{25, 1};
		interpreter::coordinates 	clear_pos{1, 24};

		interpreter::parser 		p;
		p.load_board_from_filename("data/sets/original/test01.brd");

		d.clear_terminal();

		while(true) {

			char input;
			d.draw_board_borders(borders_pos, p.get_board());
			d.draw_board(board_pos, p.get_board());
			d.draw_cursor(p.get_cursor().get_position(), board_pos, p.get_board());
			d.draw_stack(stack_pos, p.get_stack());

			std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<">>";
			d.refresh();
				
			try {
				std::cin>>input;
			}
			catch(std::exception& e) {
				std::cin.clear();
			}

			p.step();
		}

		//Exit cleanly...
		std::cout<<tools::s::pos(clear_pos.x, clear_pos.y);
		std::flush(std::cout);
	}


};

}

#endif
