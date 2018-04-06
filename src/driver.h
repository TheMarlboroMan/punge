#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>

#include "board.h"
#include "display.h"
#include "cursor.h"

namespace app {

class driver {

	public:

	void		run() {

		//TODO: Check terminal size!!!!!.

		board b(20, 20);
		display d;
		cursor c;

		coordinates board_pos{2,2};
		coordinates borders_pos{1,1};
		coordinates input_pos{1, 23};
		coordinates clear_pos{1, 24};

		while(true) {

			char input;
			try {
				d.draw_board_borders(borders_pos, b);
				d.draw_board(board_pos, b);
				d.draw_cursor(c.get_position(), board_pos, b);
				//TODO: DRAW THE STACK!!!.
				std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<">>";
				d.refresh();
				std::cin>>input;

				step(b, c);
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

	void step(const board& _b, cursor& _c) {

		auto np=_b.get_movement_position(_c.get_position(), _c.get_heading());
		_c.set_position(np);

		switch(_b.get_tile(np).get_val()) {
			case tile::noop: //Everything's cool...
				break;
			default:
			case tile::move_up:
				_c.set_heading(directions::up); break;
			case tile::move_down:
				_c.set_heading(directions::down); break;
			case tile::move_right:
				_c.set_heading(directions::right); break;
			case tile::move_left:
				_c.set_heading(directions::left); break;
			default:
				//TODO: if is alphanumeric, add to 
			break;
		}

	}

};

}

#endif
