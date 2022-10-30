#pragma once
#include "exception.h"
#include "display_interface.h"
#include <vector>

namespace app {

struct display_cell {

	char		contents;
	display_interface::color_fg	fg;
	display_interface::color_bg bg;	
	bool		dirty;
};

class buffered_terminal_display:
	public display_interface {

	public:

						buffered_terminal_display(const display_size&);
	virtual void				clear();
	virtual void				cleanup();
	virtual void				refresh();
	virtual void				draw(interpreter::coordinates, const std::string&, color_fg, color_bg);
	virtual void				draw(const std::string&, color_fg, color_bg);
	virtual std::size_t		get_w() const;
	virtual std::size_t		get_h() const;

	private:

	bool					check_size();

	const unsigned				min_w=80, min_h=27;

	const display_size&		dsize;
	interpreter::coordinates    cursor;	
	std::vector<display_cell> 	cells;
};

}

