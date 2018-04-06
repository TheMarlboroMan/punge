#ifndef STACK_H
#define STACK_H

//TODO: Fuck the tile thing.
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

	//TODO: actually, the stack should be a stack of integers, not of tiles.
	//TODO: To pop the value as ASCII we would do modulo 256.
	std::vector<tile>	items;
};

}

#endif
