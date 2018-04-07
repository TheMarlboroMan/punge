#include <iostream>
#include <stdexcept>

#include "src/app/driver.h"

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
