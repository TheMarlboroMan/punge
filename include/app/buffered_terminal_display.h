#pragma once
#include "exception.h"
#include "display_interface.h"
#include <vector>
#include <lm/logger.h>

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

						buffered_terminal_display(const display_size&, lm::logger&);
	virtual void				clear();
	virtual void				cleanup();
	virtual void				refresh();
	virtual void				draw(interpreter::coordinates, const std::string&, color_fg, color_bg);
	virtual void				draw(const std::string&, color_fg, color_bg);
	virtual std::size_t		get_w() const;
	virtual std::size_t		get_h() const;

	private:

	bool					check_size();
	
	//80 width, and then 25 height for the board, plus one for title and one for output line.
	const unsigned				min_w=80, min_h=27;

	const display_size&		dsize;
	lm::logger&                 logger;
	interpreter::coordinates    cursor;	
	std::vector<display_cell> 	cells;
	std::size_t                 dirty_cell_count{0};
};

}

