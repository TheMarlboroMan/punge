#include "app/state_play.h"
#include "app/drawing_routines.h"
#include <sstream>

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

	if(parser.is_waiting_for_char()) {

		if(_i.is_char()) {

			user_input=_i.get_char();
		}
		else if(_i.is_enter() && user_input.size()) {

			parser.push_char(user_input[0]);
			user_input.clear();
		}
	}
	else if(parser.is_waiting_for_int()) {

		if(_i.is_char()) {

			char c=_i.get_char();
			if(c >= 48 && c <= 57) {

				user_input+=c;
			}
			//TODO: What about negative integers? -> if stack size, yes.
			//TODO: is this cell size or stack size????? I would say this is stack size.
		}
		else if(_i.is_backspace() && user_input.size()) {

			user_input.pop_back();
		}
		else if(_i.is_enter() && user_input.size()) {

			//TODO: should we do any filtering of limits here??
			parser.push_int(std::stoi(user_input));
			user_input.clear();
		}
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

	if(parser.is_waiting_for_char()) {

		std::stringstream ss;
		ss<<"Enter a character, hit ENTER to finish ["<<user_input<<"]";
		draw_title(_di, ss.str());
	}
	else if(parser.is_waiting_for_int()) {

		std::stringstream ss;
		ss<<"Enter a number, hit ENTER to finish ["<<user_input<<"]";
		draw_title(_di, ss.str());
	}
	else {
	
		draw_title(_di, "Interpreter mode");
	}

	_di.refresh();
}

void state_play::do_logic(
	t_time& _last_tick
) {

	auto diff_tick=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-_last_tick);
	if(diff_tick.count() >= tick_speed) {

		_last_tick=std::chrono::system_clock::now();

		//the parser will only play if not waiting for input.
		if(parser.is_playing()) {

			parser.step();
		}
	}

	if(parser.is_end()) {
	//TODO: Figure out a way to do this...
	//	state=states::exit;
	}
}
