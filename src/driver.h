#ifndef DRIVER_H
#define DRIVER_H

#include "board.h"
#include "display.h"

namespace app {

class driver {

	public:

	void		run() {

		board b(20, 10);
		display d;
		d.draw_board(b);
	}

	private:

};

}

#endif
