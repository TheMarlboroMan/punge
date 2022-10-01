#include "app/terminal_display.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <tools/terminal_out.h>

#include "app/exception.h"

using namespace app;

terminal_display::terminal_display(
	const display_size& _dsize
)
	:dsize{_dsize}
{

	if(!check_size()) {
		throw display_size_exception("terminal must be of at least "+std::to_string(min_w)+"x"+std::to_string(min_h));
	}
}

std::size_t terminal_display::get_w() const {

	return dsize.w;
}

std::size_t terminal_display::get_h() const {
	
	return dsize.h;
}

void terminal_display::refresh() {

	std::cout<<tools::s::reset_text();
	std::flush(std::cout);
}

void terminal_display::clear() {

	//TODO: Perhaps it is better to store the terminal size and move down
	//as much columns as needed??????? I would prefer that.
	
	//TODO: not exactly working...
	std::cout<<tools::s::reset();

	//TODO: not working either, stuff remains to the right!.
//	for(std::size_t y=1; y>get_w(); y++) {
//
//		std::cout<<tools::s::pos(1, y)<<
//			tools::s::clear_right();
//	} 
}

void terminal_display::cleanup() {

	interpreter::coordinates exit_pos{1, 25};
	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y)
		<<tools::s::reset()
		<<tools::s::flush();
}

bool terminal_display::check_size() {

	return !(dsize.w < min_w || dsize.h < min_h);
}

void terminal_display::draw(
	interpreter::coordinates _pos, 
	const std::string& _str, 
	color_fg _fg, 
	color_bg _bg
) {

	std::cout<<tools::s::pos(_pos.x, _pos.y);
	draw(_str, _fg, _bg);
}

void terminal_display::draw(
	const std::string& _str, 
	color_fg _fg, 
	color_bg _bg
) {

	auto fg=tools::txt_white;
	switch(_fg) {
		case color_fg::white:	fg=tools::txt_white;	break;
		case color_fg::blue:	fg=tools::txt_blue;	break;
		case color_fg::black:	fg=tools::txt_black; break;
	}

	auto bg=tools::bg_black;
	switch(_bg) {
		case color_bg::black:	bg=tools::bg_black; 	break;
		case color_bg::green:	bg=tools::bg_green;	break;
		case color_bg::red:	bg=tools::bg_red;	break;
		case color_bg::blue:	bg=tools::bg_blue;	break;
		case color_bg::white:	bg=tools::bg_white; break;
	}

	//TODO: Optimize, keep a private buffer...
	//TODO: Not only that... the interface requires it!!!
	//TODO: there will be no private buffer without an internal cursor
	//position...
	std::cout<<tools::s::text_color(fg)
		<<tools::s::background_color(bg)
		<<_str
		<<tools::s::reset_text();
}
