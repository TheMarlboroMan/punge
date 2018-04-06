#ifndef TILE_H
#define TILE_H

namespace app {

class tile {

	public:

//TODO: Uncomment as we implement them...
	static const char noop=' ';
//	static const char addition='+';
//	static const char substraction='-';
//	static const char multiplication='*';
//	static const char division='/'; // 	Integer division: Pop a and b, then push b/a, rounded towards 0.
//	static const char modulo='%';	// 	Modulo: Pop a and b, then push the remainder of the integer division of b/a.
//	static const char logical_not='!'; //	Logical NOT: Pop a value. If the value is zero, push 1; otherwise, push zero.
//	static const char greater_than='`'; // 	Greater than: Pop a and b, then push 1 if b>a, otherwise zero.
	static const char move_right='>';
	static const char move_left='<';
	static const char move_up='^';
	static const char move_down='v';
//	static const char move_random='?';
//	static const char horizontal_if='_'; //	Pop a value; move right if value=0, left otherwise
//	static const char vertical_if='|'; //	Pop a value; move down if value=0, up otherwise
//	static const char string_delimiter='"';
//	static const char duplicate=':';
//	static const char swap='\';
//	static const char pop='$';	//	Pop value from the stack and discard it
//	static const char pop_out_int='.';// 	Pop value and output as an integer followed by a space
//	static const char pop_out_char=','; // 	Pop value and output as ASCII character
//	static const char skip='#'; // 	Bridge: Skip next cell
//	static const char put='p'; // 	A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
//	static const char get='g'; // 	A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
//	static const char push_in_int='&'; // 	Ask user for a number and push it
//	static const char push_in_char='~'; //	Ask user for a character and push its ASCII value
//	static const char end='@'; // 	End program
	//Of course, a tile can also be a-z, A-Z and 0-9 :).

			tile(char _v):val{_v}{

	};

	char		get_val() const {return val;}
	void		set_val(char _v) {val=_v;}

	private:

	char		val;

};

}

#endif
