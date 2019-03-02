#ifndef DISPLAY_INTERFACE_H
#define DISPLAY_INTERFACE_H

#include <string>

#include "../interpreter/coordinates.h"

namespace app {

//!Represents a basic display interface. 
class display_interface {

	public:

	enum class		color_fg {
		white,
		blue
	};

	enum class		color_bg {
		black,
		green,
		red,
		blue
	};

	//!Must clear the whole screen.
	virtual void		clear()=0;

	//!Must execute any memory freeing code.
	//TODO: Should execute on destruction...
	virtual void		cleanup()=0;

	//!Must effectively refresh the display.
	virtual void		refresh()=0;

	//!Must prepare a character in the given coordinates, with the specific colors.
	//!Should not directly draw it until instructed
	//!with a call to "refresh".
	//TODO: How about the "arrangement" as in vertical or horizontal???
	virtual void		draw(interpreter::coordinates, const std::string&, color_fg, color_bg)=0;

	

};

}

#endif
