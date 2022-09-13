#ifndef INTERPRETER_REGISTER_ITEM_H
#define INTERPRETER_REGISTER_ITEM_H

#include <cctype>

#include "exception.h"
#include "typedefs.h"

namespace interpreter {

struct register_item {

	t_stack			value;

					register_item(t_stack _v=0);
	bool			operator>(const register_item& _o) const;
	register_item 	operator+(const register_item& _o);
	register_item 	operator-(const register_item& _o);
	register_item 	operator*(const register_item& _o);
	register_item 	operator/(const register_item& _o);
	register_item 	operator%(const register_item& _o);
	bool			is_printable() const;
	char			as_char() const;
};

}

#endif
