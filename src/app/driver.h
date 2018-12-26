#ifndef APP_DRIVER
#define APP_DRIVER

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

	enum class states			{edit, play};

	void					do_input(const interpreter::board&);
	void					do_input_play(const interpreter::board&, const tools::terminal_in_data&);
	void					do_input_edit(const interpreter::board&, const tools::terminal_in_data&);

	void 					do_draw(display&, const interpreter::parser&);
	void 					do_draw_play(display&, const interpreter::parser&);
	void 					do_draw_edit(display&, const interpreter::parser&);

	states					state=states::edit;
	tools::terminal_in 			ti;
	interpreter::coordinates		edit_cursor;


};

}

#endif
