#pragma once

#include "display_interface.h"
#include "../interpreter/board.h"
#include "../interpreter/output.h"
#include "../interpreter/coordinates.h"
#include "../interpreter/stack.h"

namespace app {

//!Must prepare the drawing of the board.
void	draw_board(display_interface&, const interpreter::board&);

//!Must prepare the output of the program's output..
void	draw_output(display_interface&, const interpreter::output&);

//!Must prepare the drawing of the editing/interpreting cursor.
void	draw_cursor(display_interface&, const interpreter::coordinates&, const interpreter::board&, display_interface::color_fg, display_interface::color_bg);

//!Must prepare the drawing of the stack.
void	draw_stack(display_interface&, const interpreter::stack&);

//!Must prepare the drawing of the board borders.
void	draw_board_borders(display_interface&, const interpreter::board&);

//!Must prepare the drawing of the current cursor coordinates.
void	draw_cursor_pos(display_interface&, const interpreter::coordinates&);

//!Must prepare the title screen.
void	draw_title_screen(display_interface&);

//!Must draw the help screen.
void	draw_help_screen(display_interface&, const std::vector<std::string>&, std::size_t);
}

