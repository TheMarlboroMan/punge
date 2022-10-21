#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include "board.h"
#include "cursor.h"
#include "output.h"
#include "stack.h"
#include "stack_manipulator.h"

namespace interpreter {

class parser {

	public:

					parser();
	bool			is_end() const;
	const output&	get_output() const {return out;}
	const board&	get_board() const {return brd;}
	//!Returns a reference to the board. Allows changes on it.
	board&			get_board() {return brd;}
	const cursor&	get_cursor() const {return cur;}
	const stack&	get_stack() const {return stk;}

	bool			is_playing() const {return state==states::play;}
	bool			is_waiting_for_char() const {return state==states::waiting_char;}
	bool			is_waiting_for_int() const {return state==states::waiting_int;}

	//!Overwrites the current board with a new one. The original board is discarded.
	void			new_board(int _w, int _h);
	void 			load_board_from_filename(const std::string& _f);
	void			reset();
	void 			step();
	//!Pushes the given char into the stack, used for input get calls. Returns to play mode.
	void			push_char(char _val);
	//!Pushes the given integer into the stack, used for input get calls. Returns to play mode.
	void			push_int(t_stack _val);

	private:

	void			push_value_to_stack(char _val);
	void			parse_string_mode(const tile& _t);
	void	 		parse_regular_mode(const tile& _t);

	//!A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
	//We use 0 indexed coordinates.
	void			do_put_board();
	//A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
	void			do_get_board();

	directions		get_random_heading();

	cursor 				cur;
	stack				stk;
	stack_manipulator	stkman;
	board 				brd;
	output				out;
	enum class states{play, waiting_int, waiting_char} state{states::play};
	bool				end_signal=false,
						string_mode=false,
						skip_next=false;

};

}

#endif
