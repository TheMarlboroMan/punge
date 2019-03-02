#ifndef APP_TERMINAL_DISPLAY_H
#define APP_TERMINAL_DISPLAY_H

#include "exception.h"
#include "display_interface.h"

namespace app {

class terminal_display:
	public display_interface {

	public:

						terminal_display();
	void					clear();
	void					cleanup();
	void					refresh();
	void					draw(interpreter::coordinates, const std::string&, color_fg, color_bg);

	private:

	void					get_terminal_size();
	bool					check_size();

	const unsigned				min_w=80, min_h=26;

	unsigned 				w, h;
};

}

#endif
