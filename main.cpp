#include <iostream>
#include <stdexcept>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include <log.h>

#include "src/app/driver.h"

tools::log	applog("logs/app.log");

//TODO: All this shit should go into terminal tools.
//We could separate "input" and "output".

termios	initialTermios;

void flush_input() {
	//TODO: Experiment with discarding shit.
	if(0 > tcflush(STDIN_FILENO, TCIFLUSH)) {
		throw std::runtime_error("Unable to flush input");
	}
}

void enter() {

	int fl;
	if ((fl = fcntl (STDIN_FILENO, F_GETFL)) < 0) {
		throw std::runtime_error("Unable to capture stdin flags");
	}

	if (fcntl(STDIN_FILENO, F_SETFL, fl | O_NONBLOCK)) {
		throw std::runtime_error("Unable to set stdin flags");
	}

	if (0 > tcgetattr(STDIN_FILENO, &initialTermios)) {
		throw std::runtime_error("Unable save terminal attributes");
	}

	termios tios(initialTermios);
	//TODO: It would be good to choose to enable OR disable the echo.
	tios.c_lflag &= ~(ICANON);// | ECHO);	// No by-line buffering, no echo.
	tios.c_lflag &= ~(ECHO);// | ECHO);	// No by-line buffering, no echo.
//	tios.c_iflag &= ~(IXON | IXOFF);	// No ^s scroll lock
	tios.c_cc[VMIN] = 1;		// Read at least 1 character on each read().
	tios.c_cc[VTIME] = 0;		// Disable time-based preprocessing (Esc sequences)
//	tios.c_cc[VQUIT] = 0xff;		// Disable ^\. Root window will handle.
//	tios.c_cc[VSUSP] = 0xff;		// Disable ^z. Suspends in UI mode result in garbage.

	flush_input();

	if(0 > tcsetattr (STDIN_FILENO, TCSAFLUSH, &tios)) {
		throw std::runtime_error("Unable to set new attributes");
	}

}

void exit() {

	flush_input();

	if(tcsetattr (STDIN_FILENO, TCSANOW, &initialTermios)) {
		throw std::runtime_error("Unable to restore terminal state");
	}
}

struct input_data {
	char c;
	enum class arrowkeys {none, up, down, left, right} arrow;

	bool is_input() const {return c || arrow!=arrowkeys::none;}
	bool is_arrow() const {return arrow!=arrowkeys::none;}
	bool is_char() const {return c;}
	bool is_backspace() const {return c==127;}
	//TODO: And TAB????
	//TODO: And ENTER???

	input_data():c{0}, arrow{arrowkeys::none} {
	
	}
};

input_data get_input() {
	input_data res;

	//TODO like... terrible XD!.
	fd_set set;
	FD_ZERO(&set);
	FD_SET(STDIN_FILENO, &set);

	//This prevents blocking.
	timeval tv {0, 10000};
	if(select(STDIN_FILENO+1, &set, nullptr, nullptr, &tv)) {

		//TODO: Please do this right... 
		//We can either read 3 at a time and hope for the best
		//or read two if we get a scape.
		char c;
		read(STDIN_FILENO, &c, 1);

		//This is the begin of a scape sequence...
		if(c==27) {
			read(STDIN_FILENO, &c, 1);
			//This is "["
			if(c==91) {
				read(STDIN_FILENO, &c, 1);
				//These are actually the cursors!.
				switch(c) {
					case 'A': res.arrow=input_data::arrowkeys::up; break;
					case 'B': res.arrow=input_data::arrowkeys::down; break;
					case 'C': res.arrow=input_data::arrowkeys::right; break;
					case 'D': res.arrow=input_data::arrowkeys::left; break;
				}
			}
			//Control + keys and stuff... Control+C will still work :D.
			else {
				flush_input(); //Lol
			}
		}
		//Backspace, chars...
		else if(c==127 || isprint(c)) {
			res.c=c;
		}
		else {
			flush_input(); //Lol
		}
	}

	return res;
}

int main(int argc, char ** argv) {

	enter();
	std::cout<<"Hello >>"<<std::endl;

	input_data id;

	while(true) {
		std::flush(std::cout);
		id=get_input();
		if(id.is_input()) {

			if(id.is_char()) {
				std::cout<<"You said "<<id.c<<" ["<<(int)id.c<<"]"<<std::endl;
				if(id.c=='x') break;
			}
			else if(id.is_arrow()) {
				std::cout<<"Good arrow press..."<<std::endl;
			}
		}
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
