#include "display.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <terminal_out.h>

#include "exception.h"


using namespace app;

display::display()
	:board_pos{2,2},
	borders_pos{1,1},
	stack_pos{82, 1},
	output_pos{1, 23},
	input_pos{1, 24},
	exit_pos{1, 25} {

	get_terminal_size();
	if(!check_size()) {
		throw display_size_exception("terminal must be of at least "+std::to_string(min_w)+"x"+std::to_string(min_h));
	}
}

void display::refresh() {

	std::cout<<tools::s::reset_text();
	std::flush(std::cout);
}

void display::clear_terminal() {

	//TODO: Perhaps it is better to store the terminal size and move down
	//as much columns as needed??????? I would prefer that.
	std::cout<<tools::s::reset();
}

void display::draw_board(const interpreter::board& _b) {

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
}

void display::draw_output(const interpreter::output& _o) {

	const interpreter::coordinates& _pos=output_pos; //alias.
	std::cout<<tools::s::text_color(tools::txt_white)
		<<tools::s::background_color(tools::bg_green)
		<<tools::s::pos(_pos.x, _pos.y)
		<<_o.get()
		<<tools::s::reset_text();

}

void display::draw_cursor(const interpreter::coordinates& _pos, const interpreter::board& _b) {

	const interpreter::coordinates& _offset=board_pos;

	std::cout<<tools::s::text_color(tools::txt_white)
		<<tools::s::background_color(tools::bg_red)
		<<tools::s::pos(_pos.x+_offset.x, _pos.y+_offset.y)
		<<_b.get_tile(_pos).get_val()
		<<tools::s::reset_text();
}

void display::draw_stack(const interpreter::stack& _s) {

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
}

void display::draw_board_borders(const interpreter::board& _b) {

	const interpreter::coordinates& _pos=borders_pos;

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
	draw_ver(_pos.x+_b.get_w()+1, "\u2502");

	std::cout<<tools::s::reset_text();
}

void display::draw_cursor_pos(const interpreter::coordinates& _c) {

	std::cout<<tools::s::pos(input_pos.x, input_pos.y)<<"["<<_c.x<<","<<_c.y<<"]>>";
}

void display::cleanup() {

	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y)<<tools::s::flush();
}

void display::get_terminal_size(){

	winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	w=ws.ws_col;
	h=ws.ws_row;
}

bool display::check_size() {

	return !(w < min_w || h < min_h);
}
