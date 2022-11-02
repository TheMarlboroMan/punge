#pragma once
#include "board.h"
#include "board_extension.h"
#include "cursor.h"
#include "output.h"
#include "stack.h"
#include "stack_manipulator.h"
#include <lm/logger.h>
namespace interpreter {

class parser {

	public:

					parser(lm::logger&);
	bool			is_end() const;
	const output&	get_output() const {return out;}
	const board&	get_board() const {return brd;}
	board&			get_board() {return brd;}
	const board_extension& get_board_extension() const {return brd_extension;}

	const cursor&	get_cursor() const {return cur;}
	const stack&	get_stack() const {return stk;}

	bool			is_playing() const {return state==states::play;}
	bool			is_waiting_for_char() const {return state==states::waiting_char;}
	bool			is_waiting_for_int() const {return state==states::waiting_int;}

	void			set_board(const board& _b) {brd=_b;}
	void			set_board_extension(const board_extension& _e) {brd_extension=_e;}
	//!Overwrites the current board with a new one. The original board is discarded.
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

	lm::logger&			logger;
	cursor 				cur;
	stack				stk;
	stack_manipulator	stkman;
	board 				brd;
	board_extension		brd_extension;
	output				out;
	enum class states{play, waiting_int, waiting_char} state{states::play};
	bool				end_signal=false,
						string_mode=false,
						skip_next=false;

};

}

