#include "app/state_help.h"
#include "app/drawing_routines.h"
#include "tools/line_width_format.h"
#include <fstream>
#include <stdexcept>

using namespace app;

state_help::state_help(
	t_state_manager& _sm,
	const display_size& _dsize
)
	:state_interface(_sm),
	dsize{_dsize}
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
		return;
	}

	if(_if.is_arrow_up()) {
	
		if(current_position > 0) {
			
			--current_position;
			must_refresh=true;
		}
	}
	else if(_if.is_arrow_down()) {

		//dsize.h-1 is the height of the screen minus one line that will
		//be used for the title.
		if(current_position+dsize.h-1 < max_position) {

			++current_position;
			must_refresh=true;
		}
	}
}

void state_help::do_draw(
	display_interface& _di
) {

	//a refresh will be called far less than input recollection, thus this is
	//the place to signal a refresh has taken place and no others are expected
	//until scrolling happens.
	if(must_refresh) {

		_di.clear();
		must_refresh=false;
	}

	draw_help_screen(_di, lines, current_position);
	draw_title(_di, "Help, press escape to return");
	_di.refresh();
}

void state_help::do_logic(
	t_time& 
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
	lines=lwf.stream_to_vector(infile, dsize.w);
	
	//set the min and max values...
	current_position=0;
	max_position=lines.size()-1;
}
