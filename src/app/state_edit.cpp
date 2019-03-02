#include "state_edit.h"
#include "drawing_routines.h"

using namespace app;

void state_edit::do_input(input_interface& _i, interpreter::board& _board) {

	if(_i.is_arrow()) {

		auto future_position=edit_cursor;

		if(_i.is_arrow_up()) {--future_position.y;}
		else if(_i.is_arrow_down()) {++future_position.y;}
		else if(_i.is_arrow_left()) {--future_position.x;}
		else if(_i.is_arrow_right()) {++future_position.x;}

		//Validate the position...
		if(_board.check_coords(future_position)) {
			edit_cursor=future_position;
		}
	}
	else if(_i.is_char()) {

		_board.set_tile(edit_cursor, _i.get_char());
	}

}

void state_edit::do_draw(display_interface& _di, const interpreter::parser& _parser) {

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	draw_cursor(_di, edit_cursor, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::green);
	draw_cursor_pos(_di, edit_cursor);

	_di.refresh();
}

void state_edit::do_logic(interpreter::parser&, t_time&) {

}
