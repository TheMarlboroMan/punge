#include "stack.h"

using namespace interpreter;

size_t stack::get_size() const {

	return items.size();
}

void stack::clear() {

	items.clear();
}

register_item stack::pop() {

	auto res=register_item{0};
	if(items.size()) {
		res.value=items.back().value;
		items.pop_back();
	}
	update_slice();
	return res;
}

void stack::push(register_item _v) {

	items.push_back(_v);
	update_slice();
}

const std::vector<register_item const *> stack::get_slice() const {

	return slice;
}

void stack::update_slice() {

	//TODO: No magic numbers....
	slice.clear();
	slice.reserve(10);

	for(auto it=items.crbegin(); it!=items.crend(); ++it) {
		slice.push_back( &(*it) );
		if(slice.size()==10) {
			break;
		}
	}
}
