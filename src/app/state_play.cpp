#include "state_play.h"
#include "drawing_routines.h"

using namespace app;

void state_play::do_input(input_interface&, interpreter::board&) {

}

void state_play::do_draw(display_interface& _di, const interpreter::parser& _parser) {

	const auto curpos=_parser.get_cursor().get_position();

	draw_board_borders(_di, _parser.get_board());
	draw_board(_di, _parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	draw_cursor(_di, curpos, _parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::red);
	draw_stack(_di, _parser.get_stack());
	draw_output(_di, _parser.get_output());
	draw_cursor_pos(_di, curpos);

	_di.refresh();
}

void state_play::do_logic(interpreter::parser& _p, t_time& _last_tick) {

	auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-_last_tick);
	if(diff_tick.count() >= tick_speed) {
		_last_tick=std::chrono::system_clock::now();
		_p.step();
	}

	if(_p.is_end()) {
	//TODO: Figure out a way to do this...
	//	state=states::exit;
	}
}
