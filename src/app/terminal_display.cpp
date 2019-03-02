#include "display.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <terminal_out.h>

#include "exception.h"


using namespace app;

terminal_display::terminal_display() {

	get_terminal_size();
	if(!check_size()) {
		throw display_size_exception("terminal must be of at least "+std::to_string(min_w)+"x"+std::to_string(min_h));
	}
}

void terminal_display::refresh() {

	std::cout<<tools::s::reset_text();
	std::flush(std::cout);
}

void terminal_display::clear() {

	//TODO: Perhaps it is better to store the terminal size and move down
	//as much columns as needed??????? I would prefer that.
	std::cout<<tools::s::reset();
}

void terminal_display::cleanup() {

	interpreter::coordinates exit_pos{1, 25};
	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y)<<tools::s::flush();
}

void terminal_display::get_terminal_size(){

	winsize ws;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	w=ws.ws_col;
	h=ws.ws_row;
}

bool terminal_display::check_size() {

	return !(w < min_w || h < min_h);
}

void terminal_display::draw(interpreter::coordinates _pos, const std::string& _str, color_fg _fg, color_bg _bg) {

	auto fg=tools::txt_white;
	switch(_fg) {
		case color_fg::white:	fg=tools::txt_white;	break;
	}

	auto fg=tools::tools::bg_black;
	switch(_bg) {
		case color_bg::black:	fg=tools::tools::bg_black; 	break;
		case color_bg::green:	fg=tools::tools::bg_green;	break;
		case color_bg::red:	fg=tools::tools::bg_red;	break;
	}

	//TODO: Optimize, keep a private buffer...
	std::cout<<tools::s::pos(_pos.x, _pos.y)
		<<tools::s::text_color(fg)
		<<tools::s::background_color(bg)
		<<_str
		<<tools::s::reset_text();
}
