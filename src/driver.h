#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <cctype>


#include "board.h"
#include "board_loader.h"
#include "display.h"
#include "cursor.h"

namespace app {

class driver {

	public:

	void		run() {

		//TODO: It would be important to separate the interpreter
		//from the game thing. The "step" part should be the 
		//interpreter, and it should actually contain the cursor,
		//instructions, stack and shit. We would just draw on top
		//of it.

		//TODO: Check terminal size!!!!!.
		//TODO: Exit if the terminal is too small.
		//TODO: Maybe save terminal size into the display???.
		//TODO: Maybe check all that shit into display???.

		display 	d;
		board_loader 	bl;
		cursor 		c;
		stack		s;

		board b=bl.from_filename("data/sets/original/test01.brd");

		coordinates board_pos{2,2};
		coordinates borders_pos{1,1};
		coordinates input_pos{1, 23};
		coordinates stack_pos{25, 1};
		coordinates clear_pos{1, 24};

		d.clear_terminal();

		while(true) {

			char input;
			try {
				d.draw_board_borders(borders_pos, b);
				d.draw_board(board_pos, b);
				d.draw_cursor(c.get_position(), board_pos, b);
				d.draw_stack(stack_pos, s);
				std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<">>";
				d.refresh();
				std::cin>>input;

				step(b, c, s);
			}
			catch(std::exception& e) {
				//TODO: I think this is it???
				std::cin.clear();
			}
		}

		//Exit cleanly...
		std::cout<<tools::s::pos(clear_pos.x, clear_pos.y);
		std::flush(std::cout);
	}

	private:

	void step(const board& _b, cursor& _c, stack& _s) {

		auto np=_b.get_movement_position(_c.get_position(), _c.get_heading());
		_c.set_position(np);

		char val=_b.get_tile(np).get_val();
		switch(val) {
			case tile::noop: //Everything's cool...
				break;
			case tile::move_up:
				_c.set_heading(directions::up); break;
			case tile::move_down:
				_c.set_heading(directions::down); break;
			case tile::move_right:
				_c.set_heading(directions::right); break;
			case tile::move_left:
				_c.set_heading(directions::left); break;
			case tile::addition: 
				_s.push(_s.pop()+_s.pop()); break;
			case tile::substraction: 
				_s.push(_s.pop()-_s.pop()); break;
			break;
			default:
				if(std::isdigit(val)) {
					//TODO: No magic numbers...
					_s.push({static_cast<register_item::t_stack>(val-48)});
				}
				else {
					_s.push({static_cast<register_item::t_stack>(val)});
				}
			break;
		}
	}

};

}

#endif
