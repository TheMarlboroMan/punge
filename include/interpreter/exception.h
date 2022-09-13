#pragma once

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

class bad_stack_peek:public std::runtime_error {
	public:
		bad_stack_peek(std::size_t _requested, std::size_t _size):std::runtime_error(
			std::string("bad peek requested ")
			+std::to_string(_requested)
			+std::string(" for stack of size ")
			+std::to_string(_size)
		) {

	}
};
