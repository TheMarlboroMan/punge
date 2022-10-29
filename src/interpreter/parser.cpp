#include "interpreter/parser.h"

#include <iostream>
#include <cctype>
#include <exception>

#include <tools/number_generator.h>
#include <lm/log.h>

#include "interpreter/board_loader.h"

extern lm::logger* applog;

using namespace interpreter;

parser::parser()
	:brd(4,4) {

}

bool parser::is_end() const {

	return end_signal;
}

void parser::load_board_from_filename(const std::string& _f) {

	board_loader 	bl;
	brd=bl.from_filename(_f);
}

void parser::new_board(int _w, int _h) {

	brd=board(_w, _h);
}

void parser::reset() {

	out.clear();
	stk.clear();

	//TODO: Reset cursor, board...
	end_signal=false;
	string_mode=false;
	skip_next=false;
}

void parser::step() {

	//Execute...
	if(skip_next) {
		skip_next=false;
	}
	else {
		const auto& pos=cur.get_position();
		if(string_mode) {
			parse_string_mode(brd.get_tile(pos));
		}
		else {
			parse_regular_mode(brd.get_tile(pos));
		}
	}

	//...and move.
	if(state==states::play) {

		cur.set_position(brd.get_movement_position(cur.get_position(), cur.get_heading()));
	}
}

void parser::push_char(char _val) {

lm::log(*applog).info()<<"push_char("<<_val<<")"<<std::endl;

	stk.push({static_cast<t_stack>(_val)});
	state=states::play;
	//we also move the cursor, less we want to be in the same position we were...
	cur.set_position(brd.get_movement_position(cur.get_position(), cur.get_heading()));
}

void parser::push_int(t_stack _val) {


lm::log(*applog).info()<<"push_int("<<_val<<")"<<std::endl;
	stk.push({_val});
	state=states::play;
	//see push_char...
	cur.set_position(brd.get_movement_position(cur.get_position(), cur.get_heading()));
}

void parser::push_value_to_stack(char _val) {

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

void parser::parse_string_mode(const tile& _t) {

	char val=_t.get_val();
	if(val==tile::string_delimiter) {

		string_mode=!string_mode;
	}
	else {

		push_value_to_stack(val);
	}
}

void parser::parse_regular_mode(const tile& _t) {

	char val=_t.get_val();

	switch(val) {
		case tile::noop: /*Everything's cool...*/ break;

		case tile::move_up:		cur.set_heading(directions::up); break;
		case tile::move_down:		cur.set_heading(directions::down); break;
		case tile::move_right:		cur.set_heading(directions::right); break;
		case tile::move_left:		cur.set_heading(directions::left); break;
		case tile::horizontal_if:	cur.set_heading(stk.pop().value ? directions::left : directions::right); break;
		case tile::vertical_if:		cur.set_heading(stk.pop().value ? directions::up : directions::down); break;
		case tile::move_random:		cur.set_heading(get_random_heading()); break;

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

		case tile::put:			do_put_board(); break;
		case tile::get:			do_get_board(); break;

		case tile::string_delimiter:	string_mode=!string_mode; break;
		case tile::skip:		skip_next=true; break;
		case tile::end:			end_signal=true; break;
		case tile::push_in_int: state=states::waiting_int; break;
		case tile::push_in_char: state=states::waiting_char; break;
		default:				push_value_to_stack(val); break;

	}
}

//!A "put" call (a way to store a value for later use). Pop y, x, and v, then change the character at (x,y) in the program to the character with ASCII value v
//We use 0 indexed coordinates.
void parser::do_put_board() {

	try {
		auto y=stk.pop(), x=stk.pop(), v=stk.pop();
lm::log(*applog).info()<<"do_put_board:"<<x.value<<","<<y.value<<" => "<<v.value<<std::endl;
		brd.set_tile( {static_cast<int>(x.value), static_cast<int>(y.value)}, v.as_char());
	}
	catch(out_of_bounds_exception& e) {
		//It's ok...
	}
}

//A "get" call (a way to retrieve data in storage). Pop y and x, then push ASCII value of the character at that position in the program
void parser::do_get_board() {

	try {
		auto y=stk.pop(), x=stk.pop();
		const auto& t=brd.get_tile({static_cast<int>(x.value), static_cast<int>(y.value)});
		stk.push({static_cast<t_stack>(t.get_val())});
lm::log(*applog).info()<<"do_get_board:"<<x.value<<","<<y.value<<" => "<<t.get_val()<<std::endl;
	}
	catch(out_of_bounds_exception& e) {
		stk.push({0});
	}
}

directions parser::get_random_heading() {

	tools::int_generator g(0, 3);
	switch(g()) {
		case 0: return directions::up; break;
		case 1: return directions::right; break;
		case 2: return directions::down; break;
		case 3: return directions::left; break;
	}

	return directions::up; //Shut up compiler...
}
