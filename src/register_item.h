#ifndef REGISTER_ITEM_H
#define REGISTER_ITEM_H

#include <cctype>

namespace app {

struct register_item {

	typedef	unsigned 	t_stack;
	t_stack			value;

	register_item operator+(const register_item& _o) {
		register_item res;
		res.value=value+_o.value;
		return res;
	}

	register_item operator-(const register_item& _o) {
		register_item res;
		res.value=value-_o.value;
		return res;
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
