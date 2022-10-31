#include "app/state_stack.h"
#include "app/drawing_routines.h"
#include <lm/log.h>
using namespace app;

state_stack::state_stack(
	t_state_manager& _sm,
	lm::logger& _logger,
	const interpreter::stack& _stack
) 
	:state_interface(_sm, _logger),
	stack{_stack}
{
}

void state_stack::awake() {

	lm::log(logger).info()<<"state_stack awakens\n";
}

void state_stack::sleep() {

	lm::log(logger).info()<<"state_stack slumbers\n";
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

	drawing_routines dr{_di, logger};
	dr.draw_title("Current stack");
	dr.draw_stack(stack);
	_di.refresh();
}

void state_stack::do_logic(
	t_time& 
) {

}
