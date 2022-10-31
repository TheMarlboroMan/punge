#pragma once
#include <map>
#include <memory>

#include "../interpreter/coordinates.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"

#include "display_interface.h"
#include "input_interface.h"
#include "states.h"
#include "state_interface.h"
#include "typedefs.h"
#include "app/drawing_routines.h"

#include <lm/logger.h>
#include <tools/arg_manager.h>

namespace app {

class driver {

	public:

						driver(int, char **, lm::logger&);
	void					run();

	private:
	
	int 			refresh_rate=100; //Four times per second.

	void					do_input(input_interface&);

	lm::logger&					logger;
	t_state_manager				state_mngr;
	tools::arg_manager          argm;
	display_size				dsize;
	bool					exit_signal=false;
	std::map<states, std::unique_ptr<state_interface>> controllers;
};

}

