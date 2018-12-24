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
	const cursor&	get_cursor() const {return cur;}
	const stack&	get_stack() const {return stk;}

	void 			load_board_from_filename(const std::string& _f);
	void			reset();
	void 			step();

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

	bool				end_signal=false,
						string_mode=false,
						skip_next=false;

};

}

#endif
