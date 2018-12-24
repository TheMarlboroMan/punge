#ifndef APP_DISPLAY_H
#define APP_DISPLAY_H

#include "exception.h"

#include "../interpreter/board.h"
#include "../interpreter/output.h"
#include "../interpreter/coordinates.h"
#include "../interpreter/stack.h"

namespace app {

//TODO: Should this keep state as a class or do we have these as free floating
//stuff???

class display {

	public:

							display();
	void					refresh();
	void					clear_terminal();
	void					draw_board(const interpreter::board& _b);
	void					draw_output(const interpreter::output& _o);
	//!Draws the position of the parser cursor.
	void					draw_cursor(const interpreter::coordinates& _pos, const interpreter::board& _b);
	//!Draws the position of the editing cursor.
	void					draw_edit_cursor(const interpreter::coordinates& _c, const interpreter::board& _b);
	void					draw_stack(const interpreter::stack& _s);
	void					draw_board_borders(const interpreter::board& _b);
	void					draw_cursor_pos(const interpreter::coordinates& _c);
	void					cleanup();

	private:

	void					get_terminal_size();
	bool					check_size();

	const unsigned			min_w=80, min_h=26;

	unsigned 				w, h;
	interpreter::coordinates 	board_pos,
							borders_pos,
							stack_pos,
							output_pos,
							input_pos,
							exit_pos;
};

}

#endif
