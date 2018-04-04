#ifndef DISPLAY_H
#define DISPLAY_H

#include "board.h"

namespace app {

//TODO: Should this keep state???

class display {
	public:

	void		draw_board(const app::board& _b) {

		for(int y=0; y<_b.get_h(); y++) {
			for(int x=0; x<_b.get_w(); x++) {
				std::cout<<_b.get_tile(x, y).get_val();
			}
			std::cout<<"\n";
		}

		std::flush(std::cout);
	}

	void		draw_stack() {
		//TODO...
	}

	void		draw_board_changes() {
		//TODO
	}

	private:

	void		draw_borders() {
		//TODO...
	}

};

}

#endif
