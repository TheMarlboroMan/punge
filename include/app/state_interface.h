#pragma once
#include "input_interface.h"
#include "display_interface.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"
#include "states.h" 	//t_state_manager.
#include "typedefs.h"
#include <lm/logger.h>

namespace app {

//!Will abstract away every application state.
class state_interface {

	public:

			state_interface(t_state_manager& _sm, lm::logger& _logger)
		:state_mngr(_sm),
		logger{_logger}
	{}

	//!Called when the state is activated (from another state or at startup).
	virtual void	awake()=0;
	//!Called when another controller is called to the front.
	virtual void	sleep()=0;

	//!Processes input. Should not change any unrelated internal state.
	virtual void 	do_input(input_interface&)=0;
	//!Draws.
	virtual void 	do_draw(display_interface&)=0;
	//!Does logic  Should be the one to change internal state.
	virtual void 	do_logic(t_time&)=0;

	protected:

	t_state_manager&	state_mngr;
	lm::logger&         logger;
};

}

