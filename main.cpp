#include <iostream>
#include <stdexcept>

#include <log.h>

#include <terminal_in.h>

#include "src/app/driver.h"

tools::log	applog("logs/app.log");

int main(int argc, char ** argv) {

	std::cout<<"Hello >>"<<std::endl;

	//TODO: SHOULD CLEAR ITSELF AFTER EACH PRESS!!.

	tools::terminal_in	ti;
	while(true) {
		std::flush(std::cout);
		auto id=ti.get();
		if(id) {
			if(id.is_char()) {
				std::cout<<"You said "<<id.c<<" ["<<(int)id.c<<"]"<<std::endl;
				if(id.c=='x') break;
			}
			else if(id.is_arrow()) {
				std::cout<<"Good arrow press..."<<std::endl;
			}
		}
	}

	return 0;

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
