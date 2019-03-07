#ifndef APP_STATE_INTERFACE
#define APP_STATE_INTERFACE

#include "input_interface.h"
#include "display_interface.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"
#include "states.h" 	//t_state_manager.
#include "typedefs.h"

namespace app {

//!Will abstract away every application state.
class state_interface {

	public:

			state_interface(app::t_state_manager _sm)
		:state_mngr(_sm) {

	}

	virtual void	awake();
	virtual void	sleep();
	virtual void 	do_input(input_interface&, interpreter::board&)=0;
	virtual void 	do_draw(display_interface&, const interpreter::parser&)=0;
	virtual void 	do_logic(interpreter::parser&, t_time&)=0;

	protected:

	t_state_manager&	state_mngr;
};

}

#endif
