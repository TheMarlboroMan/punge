#include "app/drawing_routines.h"
#include <sstream>
#include <tools/terminal_out.h>
#include <lm/log.h>

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

void drawing_routines::draw_board_borders(
	const interpreter::board& _b
) {
	int x_offset=(di.get_w()-_b.get_w()) / 2;
	int available_h=di.get_h()-2; //TODO: this might as well be a method
	int y_offset=(available_h-_b.get_h()) / 2;
	++y_offset; //Because we have a line for the title...

lm::log(logger).debug()<<"display: "<<di.get_w()<<"x"<<di.get_h()<<" board: "<<_b.get_w()<<"x"<<_b.get_h()<<"\n";
lm::log(logger).debug()<<"offsets: "<<x_offset<<" and "<<y_offset<<"\n";

	auto bgcolor=display_interface::color_bg::blue;
	auto draw_vertical_border=[this](int _x, int _y, int _h, const char _r, display_interface::color_bg _bg) {

		std::string str{_r};
		while(_h) {

			//Don't allow drawing outside the center portion.
			if(_y < 1 || _x < 0) {

				++_y;
				continue;
			}

			//TODO: Y may exceed the available h!!
			di.draw(
				interpreter::coordinates{_x+1, _y+1}, 
				str, 
				display_interface::color_fg::black,
				_bg
			);

			++_y;
			--_h;
		}
	};

	auto draw_horizontal_border=[this](int _x, int _y, int _w, const char _r, display_interface::color_bg _bg) {

		std::string str{_r};
		while(_w) {

			//Don't allow drawing outside the center portion.
			if(_x < 0 || _y==0) {

				++_x;
				continue;
			}

			//TODO: may exceed the available w!
			di.draw(
				interpreter::coordinates{_x+1, _y+1},
				str,
				display_interface::color_fg::black,
				_bg
			);

			++_x;
			--_w;
		}
	};

	//let's see if vertical borders fit... Also, I did not run these numbers,
	//just tested it until it worked. Might be bugs.
	switch(di.get_w() - _b.get_w()) {

		case 0: //no borders for you, we have the full screen covered!
		break;
		case 1: //only right border, we can't fit the rest!
			draw_vertical_border(x_offset+_b.get_w()+1, y_offset-2, _b.get_h()+2, ' ', bgcolor);
		break;
		default: //both borders, left and right
			draw_vertical_border(x_offset-2, y_offset-2, _b.get_h()+2, ' ', bgcolor);
			draw_vertical_border(x_offset+_b.get_w()-1, y_offset-2, _b.get_h()+2, ' ', bgcolor);
		break;
	}

	//and now the same, but with horizontal ones. There may be overdraw in the
	//corners.
	switch(di.get_h() - _b.get_h()) {

		case 0:
		break;
		case 1:
			draw_horizontal_border(x_offset-2, y_offset-2, _b.get_w()+2, ' ', bgcolor);
		break;
		default:
			draw_horizontal_border(x_offset-2, y_offset-2, _b.get_w()+2, ' ', bgcolor);
			draw_horizontal_border(x_offset-2, y_offset+_b.get_h()-1, _b.get_w()+2, ' ', bgcolor);
		break;
	}
}

void drawing_routines::draw_cursor(
	const interpreter::coordinates& _pos, 
	const interpreter::board& _b, 
	display_interface::color_fg _fg, 
	display_interface::color_bg _bg
) {

	int x_offset=(di.get_w()-_b.get_w()) / 2;
	int available_h=di.get_h()-2; //TODO: this might as well be a method
	int y_offset=(available_h-_b.get_h()) / 2;
	++y_offset; //Because we have a line for the title...

	std::string contents;
	contents+=_b.get_tile(_pos).get_val();

	di.draw(
		interpreter::coordinates{x_offset+_pos.x, y_offset+_pos.y},
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

	//Center the board...
	int x_offset=(di.get_w()-_b.get_w()) / 2;
	int available_h=di.get_h()-2; //TODO: might as well be a new method.
	int y_offset=(available_h-_b.get_h()) / 2;
	++y_offset; //again, we have a line for the title. This is ugly AF.
	
	interpreter::coordinates pos{x_offset,y_offset};

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
