#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>

#include "board.h"
#include "display.h"

namespace app {

class driver {

	public:

	void		run() {

		board b(4, 4);
		display d;
		d.draw_board_borders({1,1}, b);
		d.draw_board({2,2}, b);
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
