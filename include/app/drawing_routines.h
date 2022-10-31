#pragma once

#include "display_interface.h"
#include "../interpreter/board.h"
#include "../interpreter/output.h"
#include "../interpreter/coordinates.h"
#include "../interpreter/stack.h"
#include <lm/logger.h>
namespace app {

class drawing_routines {

	public:

				drawing_routines(display_interface&, lm::logger&);

	//!Must prepare the drawing of the board.
	void	draw_board( const interpreter::board&);

	//!Must prepare the output of the program's output..
	void	draw_output( const interpreter::output&);

	//!Must prepare the drawing of the editing/interpreting cursor.
	void	draw_cursor( const interpreter::coordinates&, const interpreter::board&, display_interface::color_fg, display_interface::color_bg);

	//!Must prepare the drawing of the stack.
	void	draw_stack( const interpreter::stack&);

	//!Must prepare the drawing of the board borders.
	void	draw_board_borders( const interpreter::board&);

	//!Must prepare the drawing of the current cursor coordinates.
	void	draw_cursor_pos( const interpreter::coordinates&);

	//!Must prepare the title screen.
	void	draw_title_screen();

	//!Must draw the help screen.
	void	draw_help_screen( const std::vector<std::string>&, std::size_t);

	//!Must draw a row with the controller title.
	void    draw_title( const std::string&);

	private:

	display_interface&                  di;
	lm::logger&                         logger;
};
}
