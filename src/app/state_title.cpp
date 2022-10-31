#include "app/state_title.h"
#include "app/drawing_routines.h"
#include <sstream>
#include <lm/log.h>
using namespace app;

state_title::state_title(
	t_state_manager& _sm,
	lm::logger& _logger
)
	:state_interface(_sm, _logger) {

}

void state_title::awake() {

	lm::log(logger).info()<<"state_title awakens\n";
}

void state_title::sleep() {

	lm::log(logger).info()<<"state_title slumbers\n";
}

void state_title::do_input(
	input_interface& _if
) {

	if(_if.is_escape()) {

		state_mngr.pop();
		return;
	}

	if(_if.is_input()) {
		lm::log(logger).debug()<<"input was entered!\n";
		state_mngr.request(states::edit);
	}
}

void state_title::do_draw(
	display_interface& _di
) {

	std::stringstream ss;
	ss<<"Punge v"<<MAJOR_VERSION<<"."<<MINOR_VERSION<<"."<<PATCH_VERSION;

	drawing_routines dr{_di, logger};
	dr.draw_title_screen();
	dr.draw_title(ss.str());
	_di.refresh();
}

void state_title::do_logic(
	t_time& 
) {

}
