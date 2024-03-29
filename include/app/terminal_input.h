#pragma once
#include <tools/terminal_in.h>

#include "input_interface.h"

namespace app {

class terminal_input:
	public input_interface {

	public:

	virtual		~terminal_input() {}

	virtual void 	collect();
	virtual bool 	is_input() const;
	virtual bool 	is_tab() const;
	virtual bool 	is_escape() const;
	virtual bool 	is_enter() const;
	virtual bool 	is_backspace() const;
	virtual bool 	is_arrow() const;
	virtual bool 	is_arrow_left() const;
	virtual bool 	is_arrow_right() const;
	virtual bool 	is_arrow_up() const;
	virtual bool 	is_arrow_down() const;
	virtual bool 	is_char() const;
	virtual char 	get_char() const;
	virtual bool    is_help() const;
	virtual bool    is_stack() const;
	private:

	tools::terminal_in 		ti;
	tools::terminal_in_data		indata;
};

}

