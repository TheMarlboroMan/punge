#include "app/state_play.h"
#include "app/drawing_routines.h"

using namespace app;

state_play::state_play(
	t_state_manager& _sm,
	interpreter::parser& _parser
) 
	:state_interface(_sm),
	parser{_parser}
{
}

void state_play::awake() {

}

void state_play::sleep() {

}

void state_play::do_input(
	input_interface& _i
) {

	if(_i.is_tab() || _i.is_escape()) {

		state_mngr.pop();
		return;
	}

	if(_i.is_help()) {

		state_mngr.request(states::help);
		return;
	}

	if(_i.is_stack()) {

		state_mngr.request(states::stack);
	}
}

void state_play::do_draw(
	display_interface& _di
) {

	const auto curpos=parser.get_cursor().get_position();

	draw_board_borders(_di, parser.get_board());
	draw_board(_di, parser.get_board());

	//TODO: Change color when in string mode!!!
	//TODO: Set a reasonable refresh rate.
	draw_cursor(_di, curpos, parser.get_board(), display_interface::color_fg::white, display_interface::color_bg::red);
	draw_output(_di, parser.get_output());
	draw_cursor_pos(_di, curpos);

	_di.refresh();
}

void state_play::do_logic(
	t_time& _last_tick
) {

	auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-_last_tick);
	if(diff_tick.count() >= tick_speed) {
		_last_tick=std::chrono::system_clock::now();
		parser.step();
	}

	if(parser.is_end()) {
	//TODO: Figure out a way to do this...
	//	state=states::exit;
	}
}
