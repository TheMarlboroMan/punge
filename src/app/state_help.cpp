#include "app/state_help.h"
#include "app/drawing_routines.h"
#include <fstream>
#include <stdexcept>
#include "tools/line_width_format.h"

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

	if(_if.is_input()) {

		state_mngr.pop();
	}

	//TODO: manage up and down.
}

void state_help::do_draw(
	display_interface& _di
) {

	//TODO: Here, draw our stuffff!!!
	//TODO: actually... It would be easy, clear screen, go to 0,0, draw
	//from cur to screen height / max and be done.
	//TODO: Sure, WHERE IS THE SCREEN HEIGHT???????
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
	//TODO: sure, sure, WHERE IS THE SCREEN WIDTH??????????????'
	lines=lwf.stream_to_vector(infile);
	
	//set the min and max values...
	current_position=0;
	max_position=lines.size()-1;
	
	//and we are done.
}
