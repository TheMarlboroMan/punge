#ifndef DISPLAY_H
#define DISPLAY_H

#include <terminaltools.h>

#include "board.h"
#include "coordinates.h"


namespace app {

//TODO: Should this keep state as a class or do we have these as free floating
//stuff???

class display {
	public:

	void		refresh() {
		std::cout<<tools::s::reset_text();
		std::flush(std::cout);
	}

	void		draw_board(const coordinates& _pos, const app::board& _b) {

		std::cout<<tools::s::text_color(tools::txt_white)<<tools::s::background_color(tools::bg_black);

		int row=0;
		for(int y=_pos.y; y<_b.get_h()+_pos.y; y++) {
			std::cout<<tools::s::pos(_pos.x, y);
			for(const auto t : _b.get_row(row++)) {
				std::cout<<(t->get_val());
			}
		}
	}

	void		draw_cursor(const coordinates& _pos, const coordinates& _offset, const board& _b) {

		std::cout<<tools::s::text_color(tools::txt_white)
			<<tools::s::background_color(tools::bg_red)
			<<tools::s::pos(_pos.x+_offset.x, _pos.y+_offset.y)
			<<_b.get_tile(_pos).get_val();
	}

	void		draw_stack() {
		//TODO... this should draw the int values and a char value too.
		//If there are more items in the stack, we should show a "more...".
	}

	void		draw_board_changes() {
		//TODO: Just in case we want to be more efficient...
	}

	void		draw_board_borders(const coordinates& _pos, const board& _b) {

		std::cout<<tools::s::text_color(tools::txt_blue)<<tools::s::background_color(tools::bg_black);

		//Terminal positions are not arranged as X, Y from 0,0 but from 1,1.
		auto draw_hor=[&_pos, &_b](int _y, const std::string& _r) {
			std::cout<<tools::s::pos(_pos.x, _y);
			for(int x=_pos.x; x<=_b.get_w()+_pos.x+1; x++) {
				std::cout<<_r;
			}
		};

		auto draw_ver=[&_pos, &_b](int _x, const std::string& _r) {
			for(int y=_pos.y; y<=_b.get_h()+_pos.y+1; y++) {
				std::cout<<tools::s::pos(_x, y)<<_r;
			}
		};

		draw_hor(_pos.y, "\u2500");
		draw_hor(_pos.y+_b.get_h()+1, "\u2500");
		draw_ver(_pos.x, "\u2502");
		draw_ver(_pos.x+_b.get_h()+1, "\u2502");
	}

	private:

};

}

#endif
