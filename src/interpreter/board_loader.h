#ifndef INTERPRETER_BOARD_LOADER_H
#define INTERPRETER_BOARD_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream> //TODO: Remove.

#include "board.h"

namespace interpreter {

class board_loader {

	public:

	board		from_string(const std::string& _s);
	board		from_filename(const std::string& _fn);

	private:

	struct boardinfo {
		unsigned	w=0, h=0;
	};

	boardinfo	get_boardinfo(const std::string& _s);
	void read_into_board(board& _b, const std::string _s);
	std::string string_from_file(std::ifstream& _f);
};

}

#endif
