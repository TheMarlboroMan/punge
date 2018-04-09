#include <iostream>
#include <stdexcept>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <log.h>

#include "src/app/driver.h"

tools::log	applog("logs/app.log");
termios	initialTermios;

void enter() {

	int fd;
	if ((fd = fcntl (STDIN_FILENO, F_GETFL)) < 0) {
		throw std::runtime_error("Unable to capture stdin flags");
	}

	if (fcntl(STDIN_FILENO, F_SETFL, fd | O_NONBLOCK)) {
		throw std::runtime_error("Unable to set stdin flags");
	}

	if (0 > tcgetattr(STDIN_FILENO, &initialTermios)) {
		throw std::runtime_error("Unable save terminal attributes");
	}

	termios tios(initialTermios);
	tios.c_lflag &= ~(ICANON); // | ECHO);	// No by-line buffering, no echo.
	tios.c_iflag &= ~(IXON | IXOFF);	// No ^s scroll lock
//	tios.c_cc[VMIN] = 1;		// Read at least 1 character on each read().
//	tios.c_cc[VTIME] = 0;		// Disable time-based preprocessing (Esc sequences)
//	tios.c_cc[VQUIT] = 0xff;		// Disable ^\. Root window will handle.
//	tios.c_cc[VSUSP] = 0xff;		// Disable ^z. Suspends in UI mode result in garbage.

	//TODO: Experiment with discarding shit.
	if(0 > tcflush(STDIN_FILENO, TCIFLUSH)) {	// Flush the input queue; who knows what was pressed.
		throw std::runtime_error("Unable to flush input");
	}

	if(0 > tcsetattr (STDIN_FILENO, TCSAFLUSH, &tios)) {
		throw std::runtime_error("Unable to set new attributes");
	}

}

void exit() {

	if(0 > tcflush(STDIN_FILENO, TCIFLUSH)) {	// Flush the input queue; who knows what was pressed.
		throw std::runtime_error("Unable to flush input");
	}

	if(tcsetattr (STDIN_FILENO, TCSANOW, &initialTermios)) {
		throw std::runtime_error("Unable to restore terminal state");
	}
}

int main(int argc, char ** argv) {

	enter();
	std::cout<<"Hello >>"<<std::endl;
	//Interestingly, line buffering is fucking us up.

	char c='\0';

	while(c!='x') {
		std::cin>>c;
		std::cout<<"You said "<<c<<std::endl;
	}

	exit();
	

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
