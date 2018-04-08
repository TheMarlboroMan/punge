#ifndef INTERPRETER_TILE_H
#define INTERPRETER_TILE_H

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
//	static const char move_random='?';
	static const char horizontal_if='_';
	static const char vertical_if='|';
	static const char string_delimiter='"';
	static const char duplicate=':';
	static const char swap='\\';
	static const char pop='$';
	static const char pop_out_int='.';
	static const char pop_out_char=',';
	static const char skip='#';
//	static const char put='p'; // 	A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
//	static const char get='g'; // 	A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
//	static const char push_in_int='&'; // 	Ask user for a number and push it
//	static const char push_in_char='~'; //	Ask user for a character and push its ASCII value
	static const char end='@';
	//Of course, a tile can also be any other character :).

			tile(char _v):val{_v}{

	};

	char		get_val() const {return val;}
	void		set_val(char _v) {val=_v;}

	private:

	char		val;

};

}

#endif
