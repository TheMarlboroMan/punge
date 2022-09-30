#include "app/state_title.h"
#include "app/drawing_routines.h"

using namespace app;

state_title::state_title(t_state_manager& _sm)
	:state_interface(_sm) {

}

void state_title::awake() {

}

void state_title::sleep() {

}

void state_title::do_input(
	input_interface& _if
) {

	if(_if.is_input()) {
		state_mngr.request(states::edit);
	}
}

void state_title::do_draw(
	display_interface& _di
) {

	draw_title_screen(_di);
	_di.refresh();
}

void state_title::do_logic(
	t_time& 
) {

}
