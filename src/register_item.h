#ifndef REGISTER_ITEM_H
#define REGISTER_ITEM_H

#include <cctype>

namespace app {

struct register_item {

	typedef	unsigned 	t_stack;
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
		return register_item(value/_o.value);
	}

	register_item operator%(const register_item& _o) {
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
