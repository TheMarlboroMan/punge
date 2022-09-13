#pragma once

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
	const register_item&						peek(std::size_t) const;

	private:

	std::vector<register_item>					items;
};

}

