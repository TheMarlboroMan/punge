#ifndef APP_DRIVER
#define APP_DRIVER

#include "../interpreter/coordinates.h"
#include "../interpreter/board.h"

#include <terminal_in.h>

namespace app {

class driver {

	public:

	void						run();

	private:

	tools::terminal_in 			ti;
	interpreter::coordinates	edit_cursor;

	void						do_input(const interpreter::board&);

};

}

#endif
