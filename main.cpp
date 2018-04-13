#include <iostream>
#include <stdexcept>

#include <log.h>

#include <terminal_in.h>

#include "src/app/driver.h"

tools::log	applog("logs/app.log");

int main(int argc, char ** argv) {

	try {
		app::driver d;
		d.run();
		return 0;
	}
	catch(std::exception& e) {
		std::cerr<<"There was a problem: "<<e.what()<<std::endl;
		return 1;
	}
}
