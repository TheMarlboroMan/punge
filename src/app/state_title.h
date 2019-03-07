#ifndef APP_STATE_TITLE
#define APP_STATE_TITLE

#include "state_interface.h"

namespace app {

//!State for the title screen.
class state_title:
	public state_interface {

	public:

		state_title(t_state_manager&);

	void	awake();
	void	sleep();
	void 	do_input(input_interface&, interpreter::board&);
	void 	do_draw(display_interface&, const interpreter::parser&);
	void 	do_logic(interpreter::parser&, t_time&);

	private:

	bool	input_received=false;

};

}

#endif
