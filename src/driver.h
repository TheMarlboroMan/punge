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

		board b(5, 5);
		display d;
		cursor c;

		d.draw_board_borders({1,1}, b);
		d.draw_board({2,2}, b);
		//TODO: Noope... add extra position to compensate borders.
		d.draw_cursor(c.get_position(), b);
		d.refresh();

		while(true) {

			char c;
			try {
				std::cin>>c;
				break;
			}
			catch(std::exception& e) {
				//TODO: I think this is it???
				std::cin.clear();
			}
		}

	}

	private:

};

}

#endif
