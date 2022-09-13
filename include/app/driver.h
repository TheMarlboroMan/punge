#ifndef APP_DRIVER
#define APP_DRIVER

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

namespace app {

class driver {

	public:

						driver();
	void					run();

	private:
	
	static const int 			refresh_rate=250; //Four times per second.

	void					do_input(input_interface&, interpreter::board&);

	t_state_manager				state_mngr;
	bool					exit_signal=false;
	std::map<states, std::unique_ptr<state_interface>> controllers;
};

}

#endif
