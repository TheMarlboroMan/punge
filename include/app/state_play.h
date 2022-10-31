#pragma once
#include "state_interface.h"
#include <string>

namespace app {

//!State for the playing phase of the application.
class state_play:
	public state_interface {

	public:

				state_play(t_state_manager&, lm::logger&, interpreter::parser&);

	void		awake();
	void		sleep();
	void 		do_input(input_interface&);
	void 		do_draw(display_interface&);
	void 		do_logic(t_time&);

	private:

	static const int tick_speed=200;

	interpreter::parser&        parser;
	std::string					user_input;
};

}

