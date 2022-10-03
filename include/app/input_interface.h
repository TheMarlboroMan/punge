#pragma once
namespace app {

//!Will abstract away different input methods.
class input_interface {

	public:

	virtual 	~input_interface() {}
	virtual void 	collect()=0;
	virtual bool 	is_input() const=0;
	virtual bool 	is_tab() const=0;
	virtual bool 	is_escape() const=0;
	virtual bool 	is_enter() const=0;
	virtual bool 	is_backspace() const=0;
	virtual bool 	is_arrow() const=0;
	virtual bool 	is_arrow_left() const=0;
	virtual bool 	is_arrow_right() const=0;
	virtual bool 	is_arrow_up() const=0;
	virtual bool 	is_arrow_down() const=0;
	virtual bool 	is_char() const=0;
	virtual char 	get_char() const=0;
	virtual bool    is_help() const=0;
	virtual bool    is_stack() const=0;
};
}

