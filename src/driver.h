#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>

#include "board.h"
#include "display.h"

namespace app {

class driver {

	public:

	void		run() {

		board b(20, 10);
		display d;
		d.draw_board(b);

		while(true) {

			char c;
			try {
				std:cin>>c;
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
