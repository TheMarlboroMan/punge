#ifndef APP_DRIVER
#define APP_DRIVER

#include <chrono>

#include "../interpreter/coordinates.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"

#include "display.h"

#include <terminal_in.h>

namespace app {

class driver {

	public:

	void					run();

	private:

	typedef					std::chrono::time_point<std::chrono::system_clock> t_time;

	enum class states			{edit, play, exit};
	static const int 			tick_speed=1000;
	static const int 			refresh_rate=250; //Four times per second.


	void					do_input(const interpreter::board&);
	//TODO: Should use an interface.
	void					do_input_play(const interpreter::board&, const tools::terminal_in_data&);
	//TODO: Should use an interface.
	void					do_input_edit(const interpreter::board&, const tools::terminal_in_data&);

	//TODO: Should use an interface.
	void 					do_draw(display&, const interpreter::parser&);
	//TODO: Should use an interface.
	void 					do_draw_play(display&, const interpreter::parser&);
	//TODO: Should use an interface.
	void 					do_draw_edit(display&, const interpreter::parser&);

	void 					do_logic(interpreter::parser&, t_time&);

	states					state=states::edit;
	//TODO: Should use an interface too, so we can swap things later!!!!.
	tools::terminal_in 			ti;
	interpreter::coordinates		edit_cursor;


};

}

#endif
