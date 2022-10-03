#include "app/state_stack.h"
#include "app/drawing_routines.h"

using namespace app;

state_stack::state_stack(
	t_state_manager& _sm,
	const interpreter::stack& _stack
) 
	:state_interface(_sm),
	stack{_stack}
{
}

void state_stack::awake() {

}

void state_stack::sleep() {

}

void state_stack::do_input(
	input_interface& _i
) {

	if(_i.is_escape()) {

		state_mngr.pop();
		return;
	}

	if(_i.is_help()) {

		state_mngr.request(states::help);
		return;
	}
}

void state_stack::do_draw(
	display_interface& _di
) {

	draw_stack(_di, stack);
	_di.refresh();
}

void state_stack::do_logic(
	t_time& 
) {

}
