#ifndef INTERPRETER_STACK_H
#define INTERPRETER_STACK_H

#include <vector>

#include "register_item.h"

//TODO: Should have a max size and throw if surpassed.

namespace interpreter {

class stack {

	public:

	size_t										get_size() const;
	void										clear();
	register_item								pop();
	void										push(register_item _v);

	//TODO... Hmmmm... this is actually game specific... I don't want it here in the interpreter!!
	const std::vector<register_item const *> 	get_slice() const;

	private:

	//TODO... Hmmmm... this is actually game specific... I don't want it here in the interpreter!!
	void 										update_slice();

	std::vector<register_item>					items;
	std::vector<register_item const *>			slice; //!Already reversed in show order.
};

}

#endif
