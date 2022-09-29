#pragma once
#include "state_interface.h"
#include <vector>
#include <string>

namespace app {

//!State for the title screen.
class state_help:
	public state_interface {

	public:

		state_help(t_state_manager&);

	void	awake();
	void	sleep();
	void 	do_input(input_interface&);
	void 	do_draw(display_interface&);
	void 	do_logic(t_time&);

	private:

	void    read_help_file();

	std::vector<std::string>    lines;
	std::size_t                 current_position{0}, //top position.
	                            max_position{0};
	bool                        must_refresh{false};
};

}

