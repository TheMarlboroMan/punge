#ifndef INTERPRETER_STACK_H
#define INTERPRETER_STACK_H

#include <vector>

#include "register_item.h"

//TODO: Should have a max size and throw if surpassed.

namespace interpreter {

class stack {

	public:

	size_t		get_size() const {
		return items.size();
	}

	void		clear() {
		items.clear();
	}

	register_item	pop() {

		auto res=register_item{0};
		if(items.size()) {
			res.value=items.back().value;
			items.pop_back();
		}
		update_slice();
		return res;
	};

	void		push(register_item _v) {
		items.push_back(_v);
		update_slice();
	};

	//TODO... Hmmmm... this is actually game specific... I don't want it here in the interpreter!!
	const std::vector<register_item const *> get_slice() const {
		return slice;
	}

	private:

	//TODO... Hmmmm... this is actually game specific... I don't want it here in the interpreter!!
	void 		update_slice() {
		//TODO: No magic numbers....
		slice.clear();
		slice.reserve(10);

		for(auto it=items.crbegin(); it!=items.crend(); ++it) {
			slice.push_back( &(*it) );
			if(slice.size()==10) break;
		}
	}

	std::vector<register_item>		items;
	std::vector<register_item const *>	slice; //!Already reversed in show order.
};

}

#endif
