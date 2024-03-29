#include "app/state_edit.h"
#include "app/drawing_routines.h"
#include <lm/log.h>

using namespace app;

state_edit::state_edit(
	t_state_manager& _sm,
	lm::logger& _logger,
	interpreter::board& _board
)
	:state_interface(_sm, _logger),
	board{_board}
{

}

void state_edit::awake() {

	lm::log(logger).info()<<"state_edit awakens\n";
}

void state_edit::sleep() {


	lm::log(logger).info()<<"state_edit slumbers\n";
}

void state_edit::do_input(
	input_interface& _i
) {

	if(_i.is_escape()) {

		state_mngr.pop();
		return;
	}

	if(_i.is_tab()) {
		state_mngr.request(states::play);
		return;
	}
	
	if(_i.is_help()) {

		state_mngr.request(states::help);
		return;
	}

	if(_i.is_stack()) {

		state_mngr.request(states::stack);
		return;
	}

	if(_i.is_arrow()) {

		auto future_position=edit_cursor;

		if(_i.is_arrow_up()) {--future_position.y;}
		else if(_i.is_arrow_down()) {++future_position.y;}
		else if(_i.is_arrow_left()) {--future_position.x;}
		else if(_i.is_arrow_right()) {++future_position.x;}

		//Validate the position...
		if(board.check_coords(future_position)) {
			edit_cursor=future_position;
		}
	}
	else if(_i.is_char()) {

		board.set_tile(edit_cursor, _i.get_char());
	}

}

void state_edit::do_draw(
	display_interface& _di
) {
	drawing_routines dr{_di, logger};
	dr.draw_board_borders(board);
	dr.draw_board(board);
	dr.draw_cursor(edit_cursor, board, display_interface::color_fg::white, display_interface::color_bg::green);
	dr.draw_cursor_pos(edit_cursor);
	dr.draw_title("Edit mode");
	_di.refresh();
}

void state_edit::do_logic(t_time&) {

}
