#ifndef CURSOR_H
#define CURSOR_H

#include "coordinates.h"
#include "directions.h"

namespace app {

class cursor {
	public:

			cursor():pos{0,0}, heading{directions::right} {

	}

	void		set_position(const coordinates& _c) {
		pos=_c;
	}

	void		set_heading(directions _d) {
		heading=_d;
	}

	const coordinates& 	get_position() const {return pos;}
	int			get_x() const {return pos.x;}
	int			get_y() const {return pos.y;}
	directions		get_heading() const {return heading;}

	private:

	coordinates	pos;
	directions	heading;

};

}

#endif
