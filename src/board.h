#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <stdexcept>

#include "tile.h"
#include "coordinates.h"

namespace app {

class board {

	public:

	struct row_iterator {
		std::vector<tile>::const_iterator 	begin,
							end;
	};

				board(int _w, int _h):w{_w}, h{_h} {

		if(!check_coords({w, h})) {
			throw std::runtime_error("Invalid board dimensions");
		}

		tiles.resize(w*h, tile::move_up);
	}

	const tile&		get_tile(int _x, int _y) const {
		if(!check_coords({_x, _y})) {
			throw std::runtime_error("Invalid coordinates received");
		}
		return tiles[ (_y*h) + _x];
	}

	row_iterator	get_row(int _y) const {
		return row_iterator{tiles.begin()+(_y*h), tiles.begin()+(_y*h)+w};
	}

	int			get_w() const {return w;}
	int			get_h() const {return h;}
	bool			check_coords(const coordinates& _c) const {
		return !(_c.x > max_w || _c.y > max_h || _c.x < min_h || _c.y < min_h);
	}

	private:



	const int 		min_w=4, min_h=4, max_w=80, max_h=24;
	int 			w, h;
	std::vector<tile>	tiles;
};

}

#endif
