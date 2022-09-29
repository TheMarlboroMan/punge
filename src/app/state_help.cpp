#include "app/state_help.h"
#include "app/drawing_routines.h"
#include "tools/line_width_format.h"
#include <tools/terminal_out.h>
#include <fstream>
#include <stdexcept>

using namespace app;

state_help::state_help(
t_state_manager& _sm
)
	:state_interface(_sm) 
{

	read_help_file();
}

void state_help::awake() {

}

void state_help::sleep() {

}

void state_help::do_input(
	input_interface& _if
) {

	if(_if.is_escape()) {

		state_mngr.pop();
	}

	must_refresh=false;
	if(_if.is_arrow_up()) {
	
		if(current_position > 0) {
			
			--current_position;
			must_refresh=true;
		}
	}
	else if(_if.is_arrow_down()) {

		if(current_position < max_position) {

			++current_position;
			must_refresh=true;
		}
	}
}

void state_help::do_draw(
	display_interface& _di
) {
	if(must_refresh) {

		_di.clear();
	}

	//TODO: don't repeat ourselves, we got this before.
	auto ts=tools::get_termsize();
	draw_help_screen(_di, lines, current_position, ts.h);	
	_di.refresh();
}

void state_help::do_logic(
	t_time& _last_tick
) {

}

void state_help::read_help_file() {

	//Take the file.../
	//TODO: This would go well with an env class so we can get it from wherever.
	std::ifstream infile("data/help.txt");
	if(!infile.is_open()) {

		throw std::runtime_error("cannot open help file");
	}

	//pass it through the helper..
	tools::line_width_format lwf;
	auto screen_size=tools::get_termsize();
	lines=lwf.stream_to_vector(infile, screen_size.w);
	//TODO: Actually, we could make good use of the height too...	
	//set the min and max values...
	current_position=0;
	max_position=lines.size()-1;
	
	//and we are done.
}
