#pragma once
#include "state_interface.h"
#include "../interpreter/coordinates.h"

namespace app {

//!State for the editing phase of the application.
class state_edit:
	public state_interface {

	public:

						state_edit(t_state_manager&, lm::logger&, interpreter::board&);

	void				awake();
	void				sleep();
	void 				do_input(input_interface&);
	void 				do_draw(display_interface&);
	void 				do_logic(t_time&);

	private:

	interpreter::board&         board;
	interpreter::coordinates	edit_cursor;

};

}

