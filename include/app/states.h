#ifndef APP_STATES_H
#define APP_STATES_H

#include "status_manager.h"

namespace app {

enum class states{
	title,
	edit,
	play,
	help
};

typedef 	status_manager<states>	t_state_manager;
}

#endif
