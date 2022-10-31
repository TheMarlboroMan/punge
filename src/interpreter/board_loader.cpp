#include "interpreter/board_loader.h"

using namespace interpreter;

board board_loader::from_string(const std::string& _s) {

	boardinfo bi=get_boardinfo(_s);
	board res(bi.w, bi.h);
	read_into_board(res, _s);
	return res;
}

board board_loader::from_filename(const std::string& _fn) {

	std::ifstream file(_fn.c_str());
	if(!file) {
		throw std::runtime_error("unable to open "+_fn+" to read board");
	}

	return from_string(string_from_file(file));
}

board_loader::boardinfo board_loader::get_boardinfo(const std::string& _s) {

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

void board_loader::read_into_board(board& _b, const std::string _s) {

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

std::string board_loader::string_from_file(std::ifstream& _f) {
	std::stringstream buf;
	buf<<_f.rdbuf();
	return buf.str();
}
