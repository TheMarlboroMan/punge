#ifndef APP_STATE_INTERFACE
#define APP_STATE_INTERFACE

#include <chrono>

#include "input_interface.h"
#include "display_interface.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"

namespace app {

//!Will abstract away every application state.
class state_interface {

	public:

	//TODO: This is repeated in the driver Please, abstract away.
	typedef					std::chrono::time_point<std::chrono::system_clock> t_time;

	virtual void do_input(input_interface&, interpreter::board&)=0;
	virtual void do_draw(display_interface&, const interpreter::parser&)=0;
	virtual void do_logic(interpreter::parser&, t_time&)=0;
};

}

#endif
