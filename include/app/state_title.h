#pragma once
#include "state_interface.h"

namespace app {

//!State for the title screen.
class state_title:
	public state_interface {

	public:

		state_title(t_state_manager&, lm::logger&);

	void	awake();
	void	sleep();
	void 	do_input(input_interface&);
	void 	do_draw(display_interface&);
	void 	do_logic(t_time&);
};

}

