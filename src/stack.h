#ifndef STACK_H
#define STACK_H

#include "tile.h"
#include "vector.h"

namespace app {

class stack {

	public:

	size_t		get_size() {
		return items.size();
	}

	tile&		pop() {
		//TODO
		return items[0];
	};

	void		push(const tile& _v) {
//TODO		items.insert()
	};

//TODO: Pass a std::function to be processed by the whole vector.
	void		walk() {

	}

	private:

	std::vector<tile>	items;
};

}

#endif
