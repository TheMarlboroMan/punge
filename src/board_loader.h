#ifndef BOARD_LOADER_H
#define BOARD_LOADER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream> //TODO: Remove.

#include "board.h"

namespace app {

class board_loader {

	public:

	board		from_string(const std::string& _s) {

		//Get boardinfo.
		boardinfo bi=get_boardinfo(_s);

		//Create board.
		board res(bi.w, bi.h);
		read_into_board(res, _s);

		//Read into board.
		return res;
	}

	board		from_filename(const std::string& _fn) {

		std::ifstream file(_fn.c_str());
		if(!file) {
			throw std::runtime_error("unable to open "+_fn+" to read board");
		}

		return from_string(string_from_file(file));
	}

	private:

	struct boardinfo {
		int 		w=0, h=0;
	};

	boardinfo	get_boardinfo(const std::string& _s) {

		boardinfo res;
		std::stringstream ss(_s);
		std::string line;

		//Read each line. Add a row and read the length without the \n (-1)
		while(std::getline(ss, line)) {
			res.h++;
			res.w=line.size() > res.w ? line.size() : res.w;
		}



		return res;
	}

	void read_into_board(board& _b, const std::string _s) {

		std::stringstream ss(_s);
		std::string line;

		//Read each line. Add a row and read the length without the \n (-1)
		int y=0;
		while(std::getline(ss, line)) {
			int x=0;
			for(char c : line) {
				_b.set_tile({x++, y}, c);
			}
			++y;
		}
	}

	std::string string_from_file(std::ifstream& _f) {
		std::stringstream buf;
		buf<<_f.rdbuf();
		return buf.str();
	}
};

}

#endif
