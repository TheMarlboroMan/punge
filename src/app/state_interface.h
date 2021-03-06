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

			state_interface(t_state_manager& _sm)
		:state_mngr(_sm) {

	}

	//!Called when the state is activated (from another state or at startup).
	virtual void	awake()=0;
	//!Called when another controller is called to the front.
	virtual void	sleep()=0;

	//TODO: Board should NOT BE A PART OF THE INTERFACE.
	//!Processes input. Should not change any unrelated internal state.
	virtual void 	do_input(input_interface&, interpreter::board&)=0;
	//!Draws.
	//TODO: Parser should NOT BE A PART OF THE INTERFACE.
	virtual void 	do_draw(display_interface&, const interpreter::parser&)=0;
	//!Does logic  Should be the one to change internal state.
	//TODO: Parser should not be part of the interface.
	virtual void 	do_logic(interpreter::parser&, t_time&)=0;

	protected:

	t_state_manager&	state_mngr;
};

}

#endif
