#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "board.h"
#include "board_extension.h"
#include <lm/logger.h>
namespace interpreter {

class board_loader {

	public:

				board_loader(lm::logger&);
	board		from_string(const std::string& _s);
	board		from_filename(const std::string& _fn);
	//the extensions are returned with this method after a call to any 
	//board loading method.
	const board_extension& get_extensions() const {return extensions;}

	private:

	struct boardinfo {
		unsigned	w=0, h=0;
		bool		is_extended{false};
	};

	boardinfo	get_boardinfo(const std::string& _s);
	void 		read_into_board(board& _b, const std::string& _s, bool);
	void 		read_extension(board_extension&, const std::string& _s);
	std::string string_from_file(std::ifstream& _f);

	lm::logger&		logger;

	//The board loader has a copy of any possible extensions that it can just
	//give away.
	board_extension		extensions;
};

}

