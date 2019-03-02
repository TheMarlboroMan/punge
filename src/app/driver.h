#ifndef APP_DRIVER
#define APP_DRIVER

#include <chrono>

#include "../interpreter/coordinates.h"
#include "../interpreter/board.h"
#include "../interpreter/parser.h"

#include "display_interface.h"
#include "input_interface.h"

namespace app {

class driver {

	public:

	void					run();

	private:

	typedef					std::chrono::time_point<std::chrono::system_clock> t_time;

	enum class states			{edit, play, exit};
	static const int 			tick_speed=1000;
	static const int 			refresh_rate=250; //Four times per second.


	void					do_input(input_interface&, interpreter::board&);
	void					do_input_play(input_interface&, const interpreter::board&);
	void					do_input_edit(input_interface&, interpreter::board&);

	void 					do_draw(display_interface&, const interpreter::parser&);
	void 					do_draw_play(display_interface&, const interpreter::parser&);
	void 					do_draw_edit(display_interface&, const interpreter::parser&);

	void 					do_logic(interpreter::parser&, t_time&);

	states					state=states::edit;
	interpreter::coordinates		edit_cursor;


};

}

#endif
