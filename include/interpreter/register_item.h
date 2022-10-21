#pragma once
#include <cctype>

#include "exception.h"
#include "typedefs.h"

namespace interpreter {

struct register_item {

	t_cell			value;

					register_item(t_cell _v=0);
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

