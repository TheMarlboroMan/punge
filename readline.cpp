#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


std::vector<std::string> read(std::istream&, std::size_t=0);
void tell(const std::vector<std::string>&);

int main(int argc, char ** argv) {

	std::stringstream ss;
	ss<<"this is a line\nand this is other\nand this certainly is the third\nand fourth\nand fifth\nand sixth of eight\nthis is seven\nand this is eight and done";
	auto pieces=read(ss);
	tell(pieces);

	std::ifstream ifile("somefile.txt");
	pieces=read(ifile);
	tell(pieces);


	ifile.clear();
	ifile.seekg(0, std::ios::beg);
	pieces=read(ifile, 20);
	tell(pieces);
	return 0;
}

void tell(
	const std::vector<std::string>& _pieces
) {

	std::cout<<_pieces.size()<<std::endl;
	for(const auto& s : _pieces) {

		std::cout<<s<<std::endl;
	}
}

//TODO: still does not take into account utf8 stuff, but that should 
//be easy enough to take care of.
std::vector<std::string> read(
	std::istream& _stream,
	std::size_t _width
) {

	std::vector<std::string> result;
	std::string line;

	while(true) {

		std::getline(_stream, line);
		
		if(_width) {

			do {

				std::size_t count=line.size() < _width ? line.size() : _width;
				result.push_back(line.substr(0, count));
				line=line.substr(count);
			} while(line.size() > 0);
		}
		else {

			result.push_back(line);
		}

		if(_stream.eof()) {

			break;
		}
	}


	return result;
}

/**
as easy as that. All we have to do is take this code into a controller that,
when built, will read the file into a sstream, for example. When the controller
is invoked we can use the sstream to generate the text again for the given
width (by the way, we would need to set up a window change function callback
so we can use it).

All that is left is to take a std::size_t with the current index and print
shit out for the window height
*/
