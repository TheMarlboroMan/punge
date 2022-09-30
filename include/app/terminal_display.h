#ifndef APP_TERMINAL_DISPLAY_H
#define APP_TERMINAL_DISPLAY_H

#include "exception.h"
#include "display_interface.h"

namespace app {

class terminal_display:
	public display_interface {

	public:

						terminal_display(const display_size&);
	virtual void				clear();
	virtual void				cleanup();
	virtual void				refresh();
	virtual void				draw(interpreter::coordinates, const std::string&, color_fg, color_bg);
	virtual std::size_t		get_w() const;
	virtual std::size_t		get_h() const;

	private:

	bool					check_size();

	const unsigned				min_w=80, min_h=26;

	const display_size&		dsize;
};

}

#endif
