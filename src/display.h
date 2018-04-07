#ifndef DISPLAY_H
#define DISPLAY_H

#include <terminaltools.h>

#include "board.h"
#include "coordinates.h"
#include "stack.h"


namespace app {

//TODO: Should this keep state as a class or do we have these as free floating
//stuff???

class display {
	public:

	void		refresh() {
		std::cout<<tools::s::reset_text();
		std::flush(std::cout);
	}

	void		clear_terminal() {
		//TODO: Perhaps it is better to store the terminal size and move down
		//as much columns as needed??????? I would prefer that.
		std::cout<<tools::s::reset();
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

	void		draw_stack(coordinates _pos, const stack& _s) {

		for(const auto &it : _s.get_slice()) {
			std::cout<<tools::s::pos(_pos.x, _pos.y++)
				<<tools::s::reset_text()
//TODO: Please, add to terminal tools as "clear rest line".
				<<"\033[0K"
				<<"[";

			if(it->is_printable()) {
				std::cout<<tools::s::text_color(tools::txt_white)
					<<tools::s::background_color(tools::bg_blue)
					<<(it->as_char());
			}
			else {
				std::cout<<tools::s::text_color(tools::txt_white)
					<<tools::s::background_color(tools::bg_red)
					<<"?";
			}
			
			std::cout<<tools::s::reset_text()
				<<"]\t["
				<<tools::s::text_color(tools::txt_white)
				<<tools::s::background_color(tools::bg_blue)
				<<(it->value)
				<<tools::s::reset_text()
				<<"]";
		}

		//TODO: CLEAR ALSO until we reach 10.

		if(_s.get_size() > 10) {
			//TODO: Perhaps show how many more???
			std::cout<<tools::s::pos(_pos.x, _pos.y++)<<"[MORE]";
		}
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
