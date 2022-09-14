#include "app/drawing_routines.h"
#include <sstream>

using namespace app;

void	app::draw_cursor_pos(
	display_interface& _di, 
	const interpreter::coordinates& _pos
) {

	const std::string output="["
		+std::to_string(_pos.x)
		+","
		+std::to_string(_pos.y)
		+"]";

	_di.draw(interpreter::coordinates{1, 24}, output, display_interface::color_fg::white, display_interface::color_bg::black);
}

void	app::draw_output(
	display_interface& _di, 
	const interpreter::output& _o
) {

	_di.draw(interpreter::coordinates{1, 23}, _o.get(), display_interface::color_fg::white, display_interface::color_bg::green);
}

void	app::draw_board_borders(
	display_interface& _di, 
	const interpreter::board& _b
) {

	const interpreter::coordinates& _pos{1,1};

	//Terminal positions are not arranged as X, Y from 0,0 but from 1,1
	auto draw_hor=[&_pos, &_b, &_di](int _y, const char _r) {

		std::string str;
		str.append(_b.get_w(), _r);
		_di.draw(interpreter::coordinates{_pos.x+1, _y},
			str, 
			display_interface::color_fg::blue, 
			display_interface::color_bg::black);
	};

	auto draw_ver=[&_pos, &_b, &_di](int _x, const char _r) {

		std::string str;
		str=_r;
		for(int y=_pos.y+1; y<=_b.get_h()+_pos.y; y++) {
			_di.draw(interpreter::coordinates{_x, y}, str, display_interface::color_fg::blue, display_interface::color_bg::black);
		}
	};

	draw_hor(_pos.y, '-');
	draw_hor(_pos.y+_b.get_h()+1, '-');

	draw_ver(_pos.x, '|');
	draw_ver(_pos.x+_b.get_w()+1, '|');

	//draw corners...
	_di.draw(interpreter::coordinates{1,1}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	_di.draw(interpreter::coordinates{_b.get_w()+2,1}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	_di.draw(interpreter::coordinates{1, _b.get_h()+2}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	_di.draw(interpreter::coordinates{_b.get_w()+2,_b.get_h()+2}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
}

void	app::draw_cursor(
	display_interface& _di, 
	const interpreter::coordinates& _pos, 
	const interpreter::board& _b, 
	display_interface::color_fg _fg, 
	display_interface::color_bg _bg
) {

	interpreter::coordinates offset{2,2};

	std::string contents;
	contents+=_b.get_tile(_pos).get_val();

	_di.draw(
		interpreter::coordinates{2+_pos.x, 2+_pos.y},
		contents, //Char to string...
		_fg, _bg);
}

void	app::draw_stack(
	display_interface& _di, 
	const interpreter::stack& _s
) {

//TODO: what happens when the board is larger?
	interpreter::coordinates pos{50, 1};

	int lines_cleared=0;

	std::stringstream ss;

	std::size_t i=0;
	while(i < 10 && i < _s.get_size()) {

		const auto it=_s.peek(i++);

		auto bg=it.is_printable() 
			? display_interface::color_bg::blue
			: display_interface::color_bg::red;

		char display=it.is_printable() 
			? it.as_char()
			: '?';

		ss.str("");
		//TODO: beware, when displayed as an integer it can be VERY large.
		//TODO: actually, we should use a FIXED width for this, so previous
		//stuff will be overwritten.
		ss<<"["<<display<<"] ["<<std::to_string(it.value)<<"]";

		_di.draw(
			interpreter::coordinates{pos.x, pos.y++},
			ss.str(),
			display_interface::color_fg::white, 
			bg
		);

		++lines_cleared;
	}

	//There will be space for 10 lines, if we cleared less, we must add
	//some whitespace there to overwrite stuff that was there before.
	while(lines_cleared < 10) {

		_di.draw(
			interpreter::coordinates{pos.x, pos.y},
			"             ", //TODO: fix the amount of space.
			display_interface::color_fg::white,
			display_interface::color_bg::black
		);
		++lines_cleared;
		++pos.y;
	}

	_di.draw(
		interpreter::coordinates{pos.x, pos.y},
		(_s.get_size() > 10 ? "[MORE]" : "[----]"),
		display_interface::color_fg::white, 
		display_interface::color_bg::blue
	);
}


void	app::draw_board(
	display_interface& _di, 
	const interpreter::board& _b
) {
	
	//the borders are at 1,1
	interpreter::coordinates pos{2,2};

	for(int y=0; y<_b.get_h(); y++) {

		std::string str;
		for(int x=0; x<_b.get_w(); ++x) {
			str+=_b.get_tile({x, y}).get_val();
		}

		_di.draw(
			interpreter::coordinates{pos.x, pos.y+y},
			str,
			display_interface::color_fg::white, 
			display_interface::color_bg::black);
	}
}


void	app::draw_title_screen(
	display_interface& _di
) {

	_di.draw(interpreter::coordinates{1, 1}, 
		"Welcome to PUNGE\n\nPress any key to start (this is a lie)", 
		display_interface::color_fg::white, display_interface::color_bg::black);
}
