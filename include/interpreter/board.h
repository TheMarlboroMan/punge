#pragma once
#include <cstddef>
#include <vector>

#include "tile.h"
#include "coordinates.h"
#include "directions.h"

namespace interpreter {

//a board is a program, stored in disk or in memory. We try to keep it 
//befunge93 compatible.
//TODO: the min and max sizes are fixed here. Extended size boards will not 
//work.
class board {

	public:

		//!Base constructor creates an empty board.
						board(int _w, int _h);
	board&				operator=(const board& _b);
	void				set_tile(const coordinates& _c, char _t);
	const tile&			get_tile(const coordinates& _c) const;

	//!Gets the position that lies _d from _from... this wraps.
	coordinates			get_movement_position(const coordinates& _from, directions _d) const;

	int					get_w() const {return w;}
	int					get_h() const {return h;}
	bool				check_dimensions(const coordinates& _c) const;
	bool				check_coords(const coordinates& _c) const;

	private:

	size_t				get_index(const coordinates& _c) const;

	const int 			min_w=4, min_h=4, max_w=80, max_h=25;
	//boards support different sizes, even if the driver does not.
	int 				w, h;
	std::vector<tile>	tiles;
};

}

