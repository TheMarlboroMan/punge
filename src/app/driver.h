#ifndef APP_DRIVER
#define APP_DRIVER

#include <map>
#include <memory>

#include "../interpreter/coordinates.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"

#include "display_interface.h"
#include "input_interface.h"
#include "state_play.h"
#include "state_edit.h"

namespace app {

class driver {

	public:

						driver();
	void					run();

	private:

	typedef					std::chrono::time_point<std::chrono::system_clock> t_time;

	enum class states{
		edit,
		play,
		exit
	};
	
	static const int 			refresh_rate=250; //Four times per second.

	void					do_input(input_interface&, interpreter::board&);

	states					state=states::edit;
	std::map<states, std::unique_ptr<state_interface>> controllers;
};

}

#endif
