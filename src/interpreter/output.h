#ifndef INTERPRETER_OUTPUT_H
#define INTERPRETER_OUTPUT_H

#include <string>
#include <cctype>

#include "typedefs.h"

//TODO: Should have a max size
namespace interpreter {

class output {

	public:

	size_t		get_size() {
		return buffer.size();
	}

	void		clear() {
		buffer.clear();
	}

	//!According to specs, the number should be printed followed by an space.
	void		add(t_stack _v) {
		buffer+=std::to_string(_v)+" ";
	}

	void		add(const char _c) {

		if(!isprint(_c)) {
			buffer+=" ";
		}
		else {
			buffer.push_back(_c);
		}
	}

	const std::string&	get() const {
		return buffer;
	}

	private:

	std::string	buffer;

};

}

#endif
