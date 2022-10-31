#include "app/buffered_terminal_display.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>

#include <tools/terminal_out.h>
#include <lm/log.h>
#include "app/exception.h"

using namespace app;

buffered_terminal_display::buffered_terminal_display(
	const display_size& _dsize,
	lm::logger& _logger
)
	:dsize{_dsize},
	logger{_logger}
{

	if(!check_size()) {
		throw display_size_exception("terminal must be of at least "+std::to_string(min_w)+"x"+std::to_string(min_h));
	}

	std::cout<<tools::s::hide();

	cursor.x=1;
	cursor.y=1;

	//We have as many cells as the display allows for.
	auto total_cells=dsize.w*dsize.h;
	cells.reserve(total_cells);

	lm::log(logger).info()<<"will reserve space for "<<dsize.w<<"x"<<dsize.h<<"="<<total_cells<<"\n";
	for(std::size_t i=0; i<total_cells; i++) {

		cells.push_back({'?', display_interface::color_fg::white, display_interface::color_bg::black, true});
	}
	clear();

	std::cout<<tools::s::reset{};
}

std::size_t buffered_terminal_display::get_w() const {

	return dsize.w;
}

std::size_t buffered_terminal_display::get_h() const {
	
	return dsize.h;
}

void buffered_terminal_display::refresh() {

	lm::log(logger).debug()<<"dirty cells: "<<dirty_cell_count<<"\n";
	if(!dirty_cell_count) {

		interpreter::coordinates exit_pos{1, 27};
		std::cout<<tools::s::pos(exit_pos.x, exit_pos.y);
		std::flush(std::cout);
		return;
	}


	auto fg=tools::txt_white,
		prev_fg=tools::txt_min;
	auto bg=tools::bg_black,
		prev_bg=tools::bg_min;
	std::size_t prev_y=0,
				prev_x=0;

	for(std::size_t y=0; y<get_h(); y++) {

		for(std::size_t x=0; x<get_w(); x++) {

			std::size_t index=(y*get_w())+x;
			auto& cell=cells[index];
//lm::log(logger).debug()<<"x: "<<x<<" y:"<<y<<" curindex: "<<index<<std::endl;
			if(!cell.dirty) {
			
				continue;
			}
			
			switch(cell.fg) {
				case color_fg::white:	fg=tools::txt_white;	break;
				case color_fg::blue:	fg=tools::txt_blue;	break;
				case color_fg::black:	fg=tools::txt_black; break;
			}

			switch(cell.bg) {
				case color_bg::black:	bg=tools::bg_black; 	break;
				case color_bg::green:	bg=tools::bg_green;	break;
				case color_bg::red:	bg=tools::bg_red;	break;
				case color_bg::blue:	bg=tools::bg_blue;	break;
				case color_bg::white:	bg=tools::bg_white; break;
			}

	//The following puerile optimizations make this thing work in tilix and
	//terminology, so I'll take them... First, do not change background color 
	//if color is the same.
			if(prev_bg != bg) {

				prev_bg=bg;
				std::cout<<tools::s::background_color(bg);
			}

	//Same, but for the foreground.
			if(prev_fg != fg) {

				prev_fg=fg;
				std::cout<<tools::s::text_color(fg);
			}

	//Finally, do not change position if we are printing in sequential cells.
			if(prev_x==x-1 && prev_y==y) {
				//Noop
			}
			else {
				std::cout<<tools::s::pos(x+1, y+1);
			}

			prev_x=x;
			prev_y=y;

			std::cout<<cell.contents;

			cell.dirty=false;	
		}
	}

	dirty_cell_count=0;
	interpreter::coordinates exit_pos{1, 27};
	std::cout<<tools::s::pos(exit_pos.x, exit_pos.y);
	std::flush(std::cout);

}

void buffered_terminal_display::clear() {

	for(auto& cell : cells) {

		cell.contents=' ';
		cell.dirty=true; //TODO: do we call "clear" after each iteration???
		cell.fg=display_interface::color_fg::white;
		cell.bg=display_interface::color_bg::black;
		++dirty_cell_count;
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

		//TODO: this forces dirty cells where there may be none...
		if(_str[i]=='\n') {

			cursor.x=1;
			cursor.y++;
			++dirty_cell_count;
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
			++dirty_cell_count;
		}

		cursor.x++;
		//break if the cursor goes out of bounds...
		if((unsigned)cursor.x > get_w()) {

			break;
		}
	}
}
