#include "drawing_routines.h"

using namespace app;

void	draw_cursor_pos(display_interface& _di, const interpreter::coordinates& _pos) {

	const std::string output="["
		+std::to_string(_pos.x)
		+","
		+std::to_string(_pos.y)
		+"]";

	_di.draw(interpreter::coordinates{1, 24}, output, _di::color::fg_white, _di::bg_black);
}

void	draw_output(display_interface& _di, const interpreter::output& _o) {

	_di.draw(interpreter::coordinates{1, 23}, _o.get(), _di::color::fg_white, _di::color::bg_green);
}

void	draw_board_borders(display_interface& _di, const interpreter::board& _b) {

/*
const interpreter::coordinates& _pos=borders_pos;

	borders_pos{1,1},

	std::cout<<tools::s::text_color(tools::txt_blue)<<tools::s::background_color(tools::bg_black);

	//Terminal positions are not arranged as X, Y from 0,0 but from 1,1
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
	draw_ver(_pos.x+_b.get_w()+1, "\u2502");

	std::cout<<tools::s::reset_text();
*/
}

void	draw_cursor(display_interface& _di, const interpreter::coordinates& _pos, const interpreter::board& _b, display_interface::color _fg, display_interface::color _bg) {

	 offset{2,2};

	_di.draw(
		interpreter::coordinates{2+_pos.x, 2+_pos.y},
		_b.get_tile(_pos).get_val(),
		_fg, _bg);
}

void	draw_stack(display_interface& _di, const interpreter::stack& _s)

/*
	//TODO: This goes against the given limits!!
	stack_pos{82, 1},

	auto _pos=stack_pos; //Copy...

	int lines_cleared=0;

	std::cout<<tools::s::reset_text();

	for(const auto &it : _s.get_slice()) {
		std::cout<<tools::s::pos(_pos.x, _pos.y++)
			<<tools::s::clear_right()
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

		++lines_cleared;
	}

	//TODO: No magic number: stack size
	while(lines_cleared < 10) {
		std::cout<<tools::s::pos(_pos.x, _pos.y++)
			<<tools::s::clear_right();
		++lines_cleared;
	}

	std::cout<<tools::s::pos(_pos.x, --_pos.y)
		<<tools::s::clear_right()
		<<(_s.get_size() > 10 ? "[MORE]" : "[----]")
		<<tools::s::reset_text();
*/
}


void	draw_board(display_interface& _di, const interpreter::board& _b) {

/*
	const interpreter::coordinates& _pos=board_pos; //alias...

	std::cout<<tools::s::text_color(tools::txt_white)<<tools::s::background_color(tools::bg_black);

	int row=0;
	for(int y=_pos.y; y<_b.get_h()+_pos.y; y++) {
		std::cout<<tools::s::pos(_pos.x, y);
		for(const auto t : _b.get_row(row++)) {
			std::cout<<(t->get_val());
		}
	}

	std::cout<<tools::s::reset_text();
*/
}
