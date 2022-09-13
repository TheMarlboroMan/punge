#include "interpreter/stack.h"
#include "interpreter/exception.h"

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
	return res;
}

void stack::push(register_item _v) {

	items.push_back(_v);
}

const register_item& stack::peek(std::size_t _depth) const {

	if(_depth >= items.size()) {

		throw bad_stack_peek(_depth, items.size());
	}

	return items.at(items.size()-_depth-1);
}
