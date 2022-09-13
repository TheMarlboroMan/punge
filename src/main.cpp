#include <iostream>
#include <stdexcept>

#include <tools/terminal_in.h>

#include "app/driver.h"

#include <lm/file_logger.h>
#include <lm/log.h>

lm::logger * applog{nullptr};

int main(int argc, char ** argv) {

	try {
		applog=new lm::file_logger("logs/applog.log");
		lm::log(*applog).info()<<"Starting session"<<std::endl;
		app::driver d;
		d.run();
		delete applog;
		return 0;
	}
	catch(std::exception& e) {
		std::cerr<<"There was a problem: "<<e.what()<<std::endl;
		return 1;
	}
}
