#pragma once
#include "state_interface.h"

namespace app {

//!State for the playing phase of the application.
class state_stack:
	public state_interface {

	public:

			state_stack(t_state_manager&, const interpreter::stack&);

	void		awake();
	void		sleep();
	void 		do_input(input_interface&);
	void 		do_draw(display_interface&);
	void 		do_logic(t_time&);

	private:

	static const int tick_speed=200;

	const interpreter::stack&        stack;

};

}

