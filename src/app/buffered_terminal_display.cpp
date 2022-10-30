#include "app/buffered_terminal_display.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <tools/terminal_out.h>

#include "app/exception.h"

using namespace app;

buffered_terminal_display::buffered_terminal_display(
	const display_size& _dsize
)
	:dsize{_dsize}
{

	if(!check_size()) {
		throw display_size_exception("terminal must be of at least "+std::to_string(min_w)+"x"+std::to_string(min_h));
	}

	std::cout<<tools::s::hide();

	cursor.x=1;
	cursor.y=1;
	auto total_cells=dsize.w*dsize.h;
	cells.reserve(total_cells);
	for(std::size_t i=0; i<total_cells; i++) {

		cells.push_back({' ', display_interface::color_fg::white, display_interface::color_bg::black, true});
	}
	clear();
}

std::size_t buffered_terminal_display::get_w() const {

	return dsize.w;
}

std::size_t buffered_terminal_display::get_h() const {
	
	return dsize.h;
}

void buffered_terminal_display::refresh() {

	//TODO: save improvements for later!
	std::cout<<tools::s::reset_text();

	for(int y=0; y<get_h(); y++) {
		for(int x=0; x<get_w(); x++) {

			auto& cell=cells[(y*get_w())+x];
			if(!cell.dirty) {
			
				continue;	
			}
			
			auto fg=tools::txt_white;
			switch(cell.fg) {
				case color_fg::white:	fg=tools::txt_white;	break;
				case color_fg::blue:	fg=tools::txt_blue;	break;
				case color_fg::black:	fg=tools::txt_black; break;
			}

			auto bg=tools::bg_black;
			switch(cell.bg) {
				case color_bg::black:	bg=tools::bg_black; 	break;
				case color_bg::green:	bg=tools::bg_green;	break;
				case color_bg::red:	bg=tools::bg_red;	break;
				case color_bg::blue:	bg=tools::bg_blue;	break;
				case color_bg::white:	bg=tools::bg_white; break;
			}

			std::cout<<tools::s::pos(x+1, y+1)
				<<tools::s::text_color(fg)
				<<tools::s::background_color(bg)
				<<cell.contents;

			cell.dirty=false;	
		}
	}	

	interpreter::coordinates exit_pos{1, 25};
	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y);
	std::flush(std::cout);

}

void buffered_terminal_display::clear() {

	for(auto& cell : cells) {

		cell.contents=' ';
		cell.dirty=true; //TODO: do we call "clear" after each iteration???
		cell.fg=display_interface::color_fg::white;
		cell.bg=display_interface::color_bg::black;
	}
}

void buffered_terminal_display::cleanup() {

	interpreter::coordinates exit_pos{1, 25};
	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y)
		<<tools::s::reset_text()
		<<tools::s::reset()
		<<tools::s::show()
		<<tools::s::flush();
}

bool buffered_terminal_display::check_size() {

	return !(dsize.w < min_w || dsize.h < min_h);
}

void buffered_terminal_display::draw(
	interpreter::coordinates _pos, 
	const std::string& _str, 
	color_fg _fg, 
	color_bg _bg
) {

	cursor=_pos;
	draw(_str, _fg, _bg);
}

void buffered_terminal_display::draw(
	const std::string& _str, 
	color_fg _fg, 
	color_bg _bg
) {

	for(std::size_t i=0; i<_str.size(); i++) {

		if(_str[i]=='\n') {

			cursor.x=1;
			cursor.y++;
			continue;
		}

		auto x=cursor.x-1, y=cursor.y-1;
		auto& cell=cells[(y*get_w())+x];
		if(cell.contents != _str[i] 
			|| cell.fg != _fg
			|| cell.bg != _bg
		) {

			cell.contents=_str[i];
			cell.fg=_fg;
			cell.bg=_bg;
			cell.dirty=true;
		}

		cursor.x++;
		//break if the cursor goes out of bounds...
		if(cursor.x > get_w()) {

			break;
		}
	}
}
