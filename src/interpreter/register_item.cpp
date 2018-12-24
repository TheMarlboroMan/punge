#include "register_item.h"

using namespace interpreter;

register_item::register_item(t_stack _v)
	:value(_v) {

}

bool register_item::operator>(const register_item& _o) const {

	return value > _o.value;
}

register_item register_item::operator+(const register_item& _o) {

	return register_item(value+_o.value);
}

register_item register_item::operator-(const register_item& _o) {

	return register_item(value-_o.value);
}

register_item register_item::operator*(const register_item& _o) {

	return register_item(value*_o.value);
}

register_item register_item::operator/(const register_item& _o) {

	if(_o.value==0) {
		throw divide_by_zero_exception("tried to divide register by zero");
	}

	return register_item(value/_o.value);
}

register_item register_item::operator%(const register_item& _o) {

	if(_o.value==0) {
		throw divide_by_zero_exception("tried to modulo register by zero");

	}
	return register_item(value%_o.value);
}

bool register_item::is_printable() const {

	return isprint(as_char());
}

char register_item::as_char() const {

	return value % 255;
}
