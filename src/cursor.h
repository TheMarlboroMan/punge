#ifndef CURSOR_H
#define CURSOR_H

#include "coordinates.h"

namespace app {

class cursor {
	public:

			cursor():x(0), y(0) {

	}

	//TODO: We should check for the validity of the position.
	void		set_position(const coordinates& _c) {
		pos=c;
	}
	
	const coordinates& 	get_position() const {return pos;}
	int			get_x() const {return pos.x;}
	int			get_y() const {return pos.y;}
	

	private:

	coordinates	pos;


};

}

#endif
