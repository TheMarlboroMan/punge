#ifndef INTERPRETER_BOARD_H
#define INTERPRETER_BOARD_H

#include <vector>
#include <stdexcept>

#include "tile.h"
#include "coordinates.h"
#include "directions.h"

namespace interpreter {

class board {

	public:

		//!Base constructor creates an empty board.
				board(int _w, int _h):w{_w}, h{_h} {

		if(!check_dimensions({w, h})) {
			throw std::runtime_error("invalid board dimensions "+std::to_string(_w)+"x"+std::to_string(_h));
		}
		tiles.resize(w*h, tile::noop);
	}

	board&			operator=(const board& _b) {
		w=_b.w;
		h=_b.h;
		tiles=_b.tiles;
		return *this;
	}

	void			set_tile(const coordinates& _c, char _t) {
		if(!check_coords({_c.x, _c.y})) {
			throw std::runtime_error("set tile out of bounds ["+std::to_string(_c.x)+","+std::to_string(_c.y)+"]");
		}

		tiles[(_c.y*h) + _c.x].set_val(_t);
	}

	const tile&		get_tile(const coordinates& _c) const {
		if(!check_coords({_c.x, _c.y})) {
			throw std::runtime_error("get tile out of bounds ["+std::to_string(_c.x)+","+std::to_string(_c.y)+"]");
		}
		return tiles[ (_c.y*h) + _c.x];
	}

	const std::vector<tile const *>	get_row(int _y) const {
		if(_y < 0 || _y >= h) {
			throw std::runtime_error("get row out of bounds ["+std::to_string(_y)+"]");
		}

		std::vector<tile const *> res;
		for(int i=_y * w; i < (_y * w)+w; i++) {
			res.push_back(&tiles[i]);
		}
		return res;
	}

	//!Gets the position that lies _d from _from... this wraps.
	coordinates		get_movement_position(const coordinates& _from, directions _d) const {
		auto res=_from;
		switch(_d) {
			case directions::up: 	--res.y; break;
			case directions::down:	++res.y; break;
			case directions::left:	--res.x; break;
			case directions::right:	++res.x; break;
		}

		if(res.x < 0) {
			res.x=w-1;
		}
		else if(res.x >= w) {
			res.x=0;
		}

		if(res.y < 0) {
			res.y=h-1;
		}
		else if(res.y >= h) {
			res.y=0;
		}

		return res;
	}

	int			get_w() const {return w;}
	int			get_h() const {return h;}
	bool			check_dimensions(const coordinates& _c) const {
		return !(_c.x > max_w || _c.y > max_h || _c.x < min_h || _c.y < min_h);
	}

	bool			check_coords(const coordinates& _c) const {
		return !(_c.x >= w || _c.y >= h || _c.x < 0 || _c.y < 0);
	}

	private:

	const int 		min_w=4, min_h=4, max_w=80, max_h=24;
	int 			w, h;
	std::vector<tile>	tiles;
};

}

#endif
