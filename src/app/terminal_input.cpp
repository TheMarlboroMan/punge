#include "terminal_input.h"

using namespace app;

void terminal_input::collect() {

	indata=ti.get();
}

bool terminal_input::is_input() const {

	return indata;
}

bool terminal_input::is_tab() const {

	return tools::terminal_in_data::types::control==indata.type 
		&& indata.control==tools::terminal_in_data::controls::tab;
}

bool terminal_input::is_escape() const {

	return tools::terminal_in_data::types::control==indata.type 
		&& indata.control==tools::terminal_in_data::controls::escape;
}

bool terminal_input::is_enter() const {

	return tools::terminal_in_data::types::control==indata.type 
		&& indata.control==tools::terminal_in_data::controls::enter;
}

bool terminal_input::is_backspace() const {

	return tools::terminal_in_data::types::control==indata.type 
		&& indata.control==tools::terminal_in_data::controls::backspace;
}

bool terminal_input::is_arrow() const {

	return tools::terminal_in_data::types::arrow==indata.type;
}
bool terminal_input::is_arrow_left() const {

	return is_arrow() && tools::terminal_in_data::arrowkeys::left==indata.arrow;
}

bool terminal_input::is_arrow_right() const {

	return is_arrow() && tools::terminal_in_data::arrowkeys::right==indata.arrow;
}
bool terminal_input::is_arrow_up() const {

	return is_arrow() && tools::terminal_in_data::arrowkeys::up==indata.arrow;
}

bool terminal_input::is_arrow_down() const {

	return is_arrow() && tools::terminal_in_data::arrowkeys::down==indata.arrow;
}

bool terminal_input::is_char() const {

	return tools::terminal_in_data::types::chr==indata.type;
}

char terminal_input::get_char() const {

	return indata.get_string_data()[0];
}
