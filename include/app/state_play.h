#ifndef APP_STATE_PLAY
#define APP_STATE_PLAY

#include "state_interface.h"

namespace app {

//!State for the playing phase of the application.
class state_play:
	public state_interface {

	public:

			state_play(t_state_manager&);

	void		awake();
	void		sleep();
	void 		do_input(input_interface&, interpreter::board&);
	void 		do_draw(display_interface&, const interpreter::parser&);
	void 		do_logic(interpreter::parser&, t_time&);

	private:

	static const int tick_speed=1000;

};

}

#endif
