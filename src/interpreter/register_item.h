#ifndef INTERPRETER_REGISTER_ITEM_H
#define INTERPRETER_REGISTER_ITEM_H

#include <cctype>

#include "exception.h"
#include "typedefs.h"

namespace interpreter {

struct register_item {

	t_stack			value;

				register_item(t_stack _v=0):value(_v) {
		
	}

	register_item operator+(const register_item& _o) {
		return register_item(value+_o.value);
	}

	register_item operator-(const register_item& _o) {
		return register_item(value-_o.value);
	}

	register_item operator*(const register_item& _o) {
		return register_item(value*_o.value);
	}

	register_item operator/(const register_item& _o) {
		if(_o.value==0) {
			throw divide_by_zero_exception("tried to divide register by zero");
		}
		return register_item(value/_o.value);
	}

	register_item operator%(const register_item& _o) {
		if(_o.value==0) {
			throw divide_by_zero_exception("tried to modulo register by zero");
		}
		return register_item(value%_o.value);
	}
	
	bool			is_printable() const {
		return isprint(as_char());
	}
	char			as_char() const {
		return value % 255;
	}
};

}

#endif
