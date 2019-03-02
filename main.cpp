#include <iostream>
#include <stdexcept>

#include <terminal_in.h>

#include "src/app/driver.h"

#include <log_tools.h>
tools::log	applog("logs/app.log");

int main(int argc, char ** argv) {

	try {
		tools::info(applog)<<"Starting session"<<tools::endl();
		app::driver d;
		d.run();
		return 0;
	}
	catch(std::exception& e) {
		std::cerr<<"There was a problem: "<<e.what()<<std::endl;
		return 1;
	}
}
