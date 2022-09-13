#include "interpreter/board.h"
#include "interpreter/exception.h"

using namespace interpreter;

board::board(int _w, int _h):w{_w}, h{_h} {

	if(!check_dimensions({w, h})) {

		throw invalid_dimensions_exception("invalid board dimensions "+std::to_string(_w)+"x"+std::to_string(_h));
	}

	tiles.resize(w*h, tile::noop);
}

board& board::operator=(const board& _b) {

	w=_b.w;
	h=_b.h;
	tiles=_b.tiles;
	return *this;
}

void board::set_tile(const coordinates& _c, char _t) {

	if(!check_coords({_c.x, _c.y})) {
		throw out_of_bounds_exception("set tile out of bounds ["+std::to_string(_c.x)+","+std::to_string(_c.y)+"]");
	}

	tiles[get_index(_c)].set_val(_t);
}

const tile&	board::get_tile(const coordinates& _c) const {

	if(!check_coords({_c.x, _c.y})) {
		throw out_of_bounds_exception("get tile out of bounds ["+std::to_string(_c.x)+","+std::to_string(_c.y)+"]");
	}
	return tiles[get_index(_c)];
}

//!Gets the position that lies _d from _from... this wraps.
coordinates	board::get_movement_position(const coordinates& _from, directions _d) const {

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

bool board::check_dimensions(const coordinates& _c) const {

	return !(_c.x > max_w || _c.y > max_h || _c.x < min_h || _c.y < min_h);
}

bool board::check_coords(const coordinates& _c) const {

	return !(_c.x >= w || _c.y >= h || _c.x < 0 || _c.y < 0);
}

size_t board::get_index(const coordinates& _c) const {

	return (_c.y*w) + _c.x;
}
