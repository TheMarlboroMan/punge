#include "interpreter/board_loader.h"
#include <lm/log.h>
#include <tools/string_utils.h>

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
	//than 80 columns or the --BEGIN_EXTENSIONS-- mark is found.
	bool has_extensions{false};
	while(std::getline(ss, line)) {

		if(line=="--BEGIN_EXTENSIONS--") {

			has_extensions=true;
			break; //stop at once, whatever follows is the extensions.
		}
		res.h++;
		res.w=line.size() > res.w ? line.size() : res.w;
	}

	res.is_extended=res.w > 80 || res.h > 25 || has_extensions;

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

		//stop if extended and extensions mark is found!!
		if(_is_extended && line=="--BEGIN_EXTENSIONS--") {

			break;
		}

		int x=0;
		for(char c : line) {
			_b.set_tile({x++, y}, c);
		}
		++y;
	}

	extensions.reset();
	if(_is_extended) {

		lm::log(logger).info()<<"board is considered extended\n";
		extensions.extended=true;
		while(std::getline(ss, line)) {

			read_extension(extensions, line);
		}
	}
}

void board_loader::read_extension(
	board_extension& _extensions,
	const std::string& _line
) {

	auto pieces=tools::explode(_line, ':', 2);
	if(2!=pieces.size()) {

		std::stringstream ss;
		ss<<"bad board extension format, missing colon in '"<<_line<<"'";
		throw std::runtime_error(ss.str());
	}	

	auto value=pieces.back(); 
	pieces.pop_back();
	auto key=pieces.back();

	auto write_string=[](
		const std::string& _key,
		const std::string& _value,
		std::string& _property
	) -> void {

		if(_property.size()) {
	
			std::stringstream ss;
			ss<<"repeated extension property "<<_key;
			throw std::runtime_error(ss.str());
		}

		_property=_value;
	};

	if(key=="author") {

		write_string(key, value, _extensions.author);
		return;
	}

	if(key=="title") {

		write_string(key, value, _extensions.title);
		return;
	}

	//the stack is just a bunch of integers separated by whitespace.
	if(key=="stack") {

		read_stack(_extensions, value);
		return;
	}

	//if a program expects nothing, the value can be empty.
	if(key=="expects") {

		write_string(key, value, _extensions.expects);
		return;
	}

	if(key=="non_writable_cells") {

		//TODO: interpret this, surely in another method.
	//TODO: inmutable cells... think this through. The idea here is to have 
	//some cells that cannot be changed. We could express it like "none",
	//"all" or "none but 1,1 2,2 4,4" "all but 1,1 2,2 3,3,". Ranges as in
	//"all but 1,1-10" would be nice, but they can always be added later.
		return;
	}

	if(key=="allowed_input") {

		write_string(key, value, _extensions.allowed_input);
		return;
	}

	std::stringstream ss;
	ss<<"unknown extension value in '"<<_line<<"'";
	throw std::runtime_error(ss.str());
}

std::string board_loader::string_from_file(std::ifstream& _f) {

	std::stringstream buf;
	buf<<_f.rdbuf();
	return buf.str();
}

void board_loader::read_stack(
	board_extension& _ext, 
	const std::string& _str
) {

	//TODO:
	//the stack is just a bunch of integers separated by whitespace
	std::stringstream ss(_str);
	t_stack value_read{0};
	while(true) {

		ss>>value_read;

		_ext.initial_stack.push_back(value_read);
		lm::log(logger).debug()<<"pushing "<<value_read<<" into the initial stack\n";
		
		if(ss.eof()) {

			break;
		}
	}

	lm::log(logger).debug()<<"pushed "<<_ext.initial_stack.size()<<" total values into the initial stack\n";
}

