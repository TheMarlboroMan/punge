#include "app/drawing_routines.h"
#include <sstream>
#include <iostream> //TODO: remove
#include <tools/terminal_out.h>

using namespace app;

drawing_routines::drawing_routines(
	display_interface& _di,
	lm::logger& _logger
):
	di{_di},
	logger{_logger}
{}

void drawing_routines::draw_cursor_pos(
	const interpreter::coordinates& _pos
) {

	const std::string output="["
		+std::to_string(_pos.x)
		+","
		+std::to_string(_pos.y)
		+"]";

	di.draw(interpreter::coordinates{1, 27}, output, display_interface::color_fg::white, display_interface::color_bg::black);
}

void drawing_routines::draw_output(
	const interpreter::output& _o
) {

	di.draw(interpreter::coordinates{1, 27}, _o.get(), display_interface::color_fg::white, display_interface::color_bg::green);
}

//TODO: Do we really need board borders? I argue that we can just use a 
//different BG color, or something
void drawing_routines::draw_board_borders(
	const interpreter::board& _b
) {

	const interpreter::coordinates& _pos{1,1};

	//Terminal positions are not arranged as X, Y from 0,0 but from 1,1
	auto draw_hor=[&_pos, &_b, this](int _y, const char _r) {

		std::string str;
		str.append(_b.get_w(), _r);
		di.draw(interpreter::coordinates{_pos.x+1, _y},
			str, 
			display_interface::color_fg::blue, 
			display_interface::color_bg::black);
	};

	auto draw_ver=[&_pos, &_b, this](int _x, const char _r) {

		std::string str;
		str=_r;
		for(int y=_pos.y+1; y<=_b.get_h()+_pos.y; y++) {
			di.draw(interpreter::coordinates{_x, y}, str, display_interface::color_fg::blue, display_interface::color_bg::black);
		}
	};

	draw_hor(_pos.y, '-');
	draw_hor(_pos.y+_b.get_h()+1, '-');

	draw_ver(_pos.x, '|');
	draw_ver(_pos.x+_b.get_w()+1, '|');

	//draw corners...
	di.draw(interpreter::coordinates{1,1}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	di.draw(interpreter::coordinates{_b.get_w()+2,1}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	di.draw(interpreter::coordinates{1, _b.get_h()+2}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
	di.draw(interpreter::coordinates{_b.get_w()+2,_b.get_h()+2}, "+", display_interface::color_fg::blue, display_interface::color_bg::black);
}

void drawing_routines::draw_cursor(
	const interpreter::coordinates& _pos, 
	const interpreter::board& _b, 
	display_interface::color_fg _fg, 
	display_interface::color_bg _bg
) {

	std::string contents;
	contents+=_b.get_tile(_pos).get_val();

	di.draw(
		interpreter::coordinates{2+_pos.x, 2+_pos.y},
		contents, //Char to string...
		_fg, _bg);
}

void drawing_routines::draw_stack(
	const interpreter::stack& _s
) {

	interpreter::coordinates pos{1, 2};

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

		di.draw(
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

		di.draw(
			interpreter::coordinates{pos.x, pos.y},
			"             ", //TODO: fix the amount of space.
			display_interface::color_fg::white,
			display_interface::color_bg::black
		);
		++lines_cleared;
		++pos.y;
	}

	di.draw(
		interpreter::coordinates{pos.x, pos.y},
		(_s.get_size() > 10 ? "[MORE]" : "[----]"),
		display_interface::color_fg::white, 
		display_interface::color_bg::blue
	);
}

void drawing_routines::draw_board(
	const interpreter::board& _b
) {
	
	//the borders are at 1,1
	interpreter::coordinates pos{2,2};

	for(int y=0; y<_b.get_h(); y++) {

		std::string str;
		for(int x=0; x<_b.get_w(); ++x) {
			str+=_b.get_tile({x, y}).get_val();
		}

		di.draw(
			interpreter::coordinates{pos.x, pos.y+y},
			str,
			display_interface::color_fg::white, 
			display_interface::color_bg::black);
	}
}

void drawing_routines::draw_title_screen() {

	di.draw(interpreter::coordinates{1, 3}, 
		"Welcome to PUNGE\n\nPress any key to start (this is a lie)", 
		display_interface::color_fg::white, display_interface::color_bg::black);
}

void drawing_routines::draw_help_screen(
	const std::vector<std::string>& _data,
	std::size_t _pos 
) {

	//TODO: This whole y=2 is... terrible, to be honest. We should have
	//a transformation offset for all these functions.
	std::size_t y=2;

	//Amount of rows available for printing discarding the title row...
	std::size_t available=di.get_h()-1; 
	while(true) {

		//-1 because we used one line for the title...
		if(_pos >= _data.size() || !available) {

			break;
		}

		di.draw(
			interpreter::coordinates{1, y++},
			_data.at(_pos),
			display_interface::color_fg::white,
			display_interface::color_bg::black
		);

		++_pos;
		--available;
	}
}

void drawing_routines::draw_title(
	const std::string& _title
) {

	std::string padding(di.get_w(), ' ');
	
	di.draw(
		interpreter::coordinates{1, 1},
		padding,
		display_interface::color_fg::black,
		display_interface::color_bg::white
	);
	
	di.draw(
		interpreter::coordinates{1, 1},
		_title,
		display_interface::color_fg::black,
		display_interface::color_bg::white
	);
}
