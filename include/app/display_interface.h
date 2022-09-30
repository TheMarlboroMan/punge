#pragma once
#include <string>

#include "../interpreter/coordinates.h"

namespace app {

//!Expresses display size in rows and columns.
struct display_size {

	std::size_t		w{0},
					h{0};
};

//!Represents a basic display interface. 
class display_interface {

	public:

	enum class		color_fg {
		white,
		blue,
		black
	};

	enum class		color_bg {
		black,
		green,
		red,
		blue,
		white
	};

	//!Must return the width of the display in columns.
	virtual std::size_t	get_w()const=0;

	//!Must return the width of the display in rows.
	virtual std::size_t get_h()const=0;
	
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

