#ifndef APP_STATE_EDIT
#define APP_STATE_EDIT

#include "state_interface.h"
#include "../interpreter/coordinates.h"

namespace app {

//!State for the editing phase of the application.
class state_edit:
	public state_interface {

	public:

					state_edit(t_state_manager&);

	void				awake();
	void				sleep();
	void 				do_input(input_interface&, interpreter::board&);
	void 				do_draw(display_interface&, const interpreter::parser&);
	void 				do_logic(interpreter::parser&, t_time&);

	private:

	interpreter::coordinates	edit_cursor;

};

}

#endif
