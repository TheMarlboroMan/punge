#include "interpreter/board_loader.h"
#include <lm/log.h>

using namespace interpreter;

board_loader::board_loader(
	lm::logger& _logger
):
	logger{_logger}
{}

board board_loader::from_string(const std::string& _s) {

	boardinfo bi=get_boardinfo(_s);
	lm::log(logger).info()<<"read boardinfo "<<bi.w<<"x"<<bi.h<<" ("<<(
		bi.is_extended ? "extended" : "b93")<<")\n";

	board res(bi.w, bi.h);
	read_into_board(res, _s, bi.is_extended);
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
	//There are some conditions under which we will consider a board to be
	//an extended format: if it has more than 25 lines, any line is larger
	//than 80 columns or the --BEGIN_METADATA-- mark is found.
	bool has_metadata{false};
	while(std::getline(ss, line)) {

		if(line=="--BEGIN_METADATA--") {

			has_metadata=true;
			break; //stop at once, whatever follows is the metadata.
		}
		res.h++;
		res.w=line.size() > res.w ? line.size() : res.w;
	}

	res.is_extended=res.w > 80 || res.h > 25 || has_metadata;

	//all non-extended maps are set to 80x25.
	if(!res.is_extended) {

		res.w=80;
		res.h=25;
	}
	return res;
}

void board_loader::read_into_board(
	board& _b, 
	const std::string& _s,
	bool _is_extended
) {

	std::stringstream ss(_s);
	std::string line;

	//Read each line. Add a row and read the length without the \n (-1)
	int y=0;
	while(std::getline(ss, line)) {

		//stop if extended and metadata mark is found!!
		if(_is_extended && line=="--BEGIN_METADATA--") {

			break;
		}

		int x=0;
		for(char c : line) {
			_b.set_tile({x++, y}, c);
		}
		++y;
	}

	if(_is_extended) {

		while(std::getline(ss, line)) {

			read_metadata(_b, line);
		}
	}
}

void board_loader::read_metadata(
	board& _b,
	const std::string& _line
) {
	//TODO:
	lm::log(logger).info()<<"read metadata line '"<<_line<<"'\n";
}

std::string board_loader::string_from_file(std::ifstream& _f) {
	std::stringstream buf;
	buf<<_f.rdbuf();
	return buf.str();
}
