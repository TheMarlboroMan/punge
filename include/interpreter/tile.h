#pragma once
#include "typedefs.h"
namespace interpreter {

class tile {

	public:

	static const char noop=' ';
	static const char addition='+';
	static const char substraction='-';
	static const char multiplication='*';
	static const char division='/';
	static const char modulo='%';
	static const char logical_not='!';
	static const char greater_than='`';
	static const char move_right='>';
	static const char move_left='<';
	static const char move_up='^';
	static const char move_down='v';
	static const char move_random='?';
	static const char horizontal_if='_';
	static const char vertical_if='|';
	static const char string_delimiter='"';
	static const char duplicate=':';
	static const char swap='\\';
	static const char pop='$';
	static const char pop_out_int='.';
	static const char pop_out_char=',';
	static const char skip='#';
	static const char put='p';
	static const char get='g';
	static const char push_in_int='&'; // 	Ask user for a number and push it
	static const char push_in_char='~'; //	Ask user for a character and push its ASCII value
	static const char end='@';
	//Of course, a tile can also be any other character :).

				tile(t_cell _v);
	t_cell		get_val() const {return val;}
	void		set_val(t_cell _v) {val=_v;}

	private:

	t_cell		val;

};

}

