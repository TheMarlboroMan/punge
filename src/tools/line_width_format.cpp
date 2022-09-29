#include <tools/line_width_format.h>
#include <sstream>

using namespace tools;

//TODO: no utf8 is taken into account.
std::vector<std::string> line_width_format::stream_to_vector(
	std::istream& _stream,
	std::size_t _width
) {

	auto str=stream_to_string(_stream, _width);
	std::vector<std::string> result;
	std::stringstream ss(str);

	std::string line{};
	while(true) {

		std::getline(ss, line);
		result.push_back(line);
		if(ss.eof()) {

			break;
		}
	}
	return result;
}

std::string line_width_format::stream_to_string(
	std::istream& _stream,
	std::size_t _width
) {

	std::string result{}, line{};
	while(true) {

		std::getline(_stream, line);
		if(_width) {

			do {

				std::size_t count=line.size() < _width
					? line.size()
					: _width;

				result+=line.substr(0, count)+'\n';
				line=line.substr(count);

			}while(line.size() > 0);
		}
		else {

			result+=line+'\n';
		}

		if(_stream.eof()) {

			break;
		}
	}

	return result;
}
