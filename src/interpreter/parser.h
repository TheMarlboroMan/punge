#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include <iostream>
#include <cctype>


#include "board.h"
#include "board_loader.h"
#include "cursor.h"
#include "output.h"
#include "stack.h"
#include "stack_manipulator.h"

namespace interpreter {

class parser {

	public:

			parser():
		b(4,4) {

	}

	bool		is_end() const {
		return end_signal;
	}

	const output&	get_output() const {
		return out;
	}

	const board&	get_board() const {
		return b;
	}

	const cursor&	get_cursor() const {
		return cur;
	}

	const stack&	get_stack() const {
		return stk;
	}

	void 		load_board_from_filename(const std::string& _f) {
		board_loader 	bl;
		b=bl.from_filename(_f);
	}

	void		reset() {

		out.clear();
		stk.clear();
		//TODO: Reset cursor, board...
		end_signal=false;
		string_mode=false;
		skip_next=false;
	}

	void 		step() {

		auto np=b.get_movement_position(cur.get_position(), cur.get_heading());
		cur.set_position(np);

		if(skip_next) {
			skip_next=false;
		}
		else if(string_mode) {
			parse_string_mode(b.get_tile(np));
		}
		else {
			parse_regular_mode(b.get_tile(np));
		}
	}

	private:

	void		push_value_to_stack(char _val) {

		if(string_mode) {
			stk.push({static_cast<t_stack>(_val)});
		}
		else {
			if(std::isdigit(_val)) {
				//TODO: No magic numbers...
				stk.push({static_cast<t_stack>(_val-48)});
			}
			else {
				stk.push({static_cast<t_stack>(_val)});
			}
		}
	}

	void		parse_string_mode(const tile& _t) {

		char val=_t.get_val();
		if(val==tile::string_delimiter) {
			string_mode=!string_mode;
		}
		else {
			push_value_to_stack(val);
		}
	}

	void 		parse_regular_mode(const tile& _t) {
		char val=_t.get_val();

		switch(val) {
			case tile::noop: /*Everything's cool...*/ break;

			case tile::move_up:		cur.set_heading(directions::up); break;
			case tile::move_down:		cur.set_heading(directions::down); break;
			case tile::move_right:		cur.set_heading(directions::right); break;
			case tile::move_left:		cur.set_heading(directions::left); break;
			case tile::horizontal_if:	cur.set_heading(stk.pop().value ? directions::left : directions::right); break;
			case tile::vertical_if:		cur.set_heading(stk.pop().value ? directions::up : directions::down); break;

			case tile::pop:			stk.pop(); break;

			case tile::addition: 		stkman.add(stk); break;
			case tile::substraction: 	stkman.substract(stk); break;
			case tile::multiplication: 	stkman.multiply(stk); break;
			case tile::division: 		stkman.divide(stk); break;
			case tile::modulo: 		stkman.modulo(stk); break;
			case tile::duplicate:		stkman.duplicate(stk); break;
			case tile::swap:		stkman.swap(stk); break;
			case tile::logical_not:		stkman.logical_not(stk); break;
			case tile::greater_than:	stkman.greater_than(stk); break;

			case tile::pop_out_int:		out.add(stk.pop().value); break;
			case tile::pop_out_char:	out.add(stk.pop().as_char()); break;

			case tile::string_delimiter:	string_mode=!string_mode; break;
			case tile::skip:		skip_next=true; break;
			case tile::end:			end_signal=true; break;

			default:			push_value_to_stack(val); break;
		}
	}

	cursor 			cur;
	//TODO: Terrible variable names...
	stack			stk;
	stack_manipulator	stkman;
	board 			b;
	output			out;

	bool		end_signal=false,
			string_mode=false,
			skip_next=false;

};

}

#endif
