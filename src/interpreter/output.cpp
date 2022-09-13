#include "interpreter/output.h"

using namespace interpreter;

size_t output::get_size() {

	return buffer.size();
}

void output::clear() {

	buffer.clear();
}

void output::add(t_stack _v) {

	buffer+=std::to_string(_v)+" ";
}

void output::add(const char _c) {

	if(!isprint(_c)) {
		buffer+=" ";
	}
	else {
		buffer.push_back(_c);
	}
}

const std::string& output::get() const {

	return buffer;
}
