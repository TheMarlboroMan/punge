#ifndef INTERPRETER_EXCEPTION_H
#define INTERPRETER_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace interpreter {

class divide_by_zero_exception:public std::runtime_error {
	public:
		divide_by_zero_exception(const std::string& _m):std::runtime_error(_m) {

	}
};

class modulo_by_zero_exception:public std::runtime_error {

	public:
		modulo_by_zero_exception(const std::string& _m):std::runtime_error(_m) {

	}
};

class invalid_dimensions_exception:public std::runtime_error {
	public:
		invalid_dimensions_exception(const std::string& _m):std::runtime_error(_m) {

	}
};

class out_of_bounds_exception:public std::runtime_error {
	public:
		out_of_bounds_exception(const std::string& _m):std::runtime_error(_m) {

	}
};

}

#endif
