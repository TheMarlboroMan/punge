#ifndef DISPLAY_H
#define DISPLAY_H

#include <terminaltools.h>

#include "board.h"
#include "coordinates.h"


namespace app {

//TODO: Should this keep state???

class display {
	public:

	void		refresh() {
		std::flush(std::cout);
	}

	void		draw_board(const coordinates& _pos, const app::board& _b) {

		for(int y=_pos.y; y<_b.get_h()+_pos.y; y++) {

			//TODO: Should they??. I think they should be.
			//Terminal positions are not arranged as X, Y from 0,0 but from 1,1.
			std::cout<<tools::s::pos(_pos.x+1, y+1);
			auto it=_b.get_row(y);
			while(it.begin < it.end) {
				std::cout<<(it.begin->get_val());
				++it.begin;
			}
		}
	}

	void		draw_stack() {
		//TODO...
	}

	void		draw_board_changes() {
		//TODO: Who should store the differences????
	}

	void		draw_board_borders(const coordinates& _pos, const board& _b) {

		//TODO: Should they??. I think they should be.
		//Terminal positions are not arranged as X, Y from 0,0 but from 1,1.
		auto draw_hor=[&_pos, &_b](int _y, char _r) {
			std::cout<<tools::s::pos(_pos.x, _y);
			for(int x=_pos.x; x<_b.get_w()+_pos.x+1; x++) {
				std::cout<<_r;
			}
		};

		auto draw_ver=[&_pos, &_b](int _x, char _r) {
			for(int y=_pos.y; y<_b.get_h()+_pos.y+1; y++) {
				std::cout<<tools::s::pos(_x, y)<<_r;
			}
		};

		draw_hor(_pos.y, 'a');
		draw_hor(_pos.y+_b.get_h()+1, 'b');
		draw_ver(_pos.x, 'c');
		draw_ver(_pos.x+_b.get_h()+1, 'd');

	}

	private:

};

}

#endif
