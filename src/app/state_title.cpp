#include "state_title.h"
#include "drawing_routines.h"

using namespace app;

void state_title::do_input(input_interface&, interpreter::board&) {

}

void state_title::do_draw(display_interface& _di, const interpreter::parser& _parser) {

	draw_title_screen(_di);
	_di.refresh();
}

void state_title::do_logic(interpreter::parser& _p, t_time& _last_tick) {

}
