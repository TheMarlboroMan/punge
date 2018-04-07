#ifndef INTERPRETER_PARSER_H
#define INTERPRETER_PARSER_H

#include <iostream>
#include <cctype>


#include "board.h"
#include "board_loader.h"
#include "cursor.h"

namespace interpreter {

class parser {

	public:

			parser():
		b(4,4) {

	}

	const board&	get_board() const {
		return b;
	}

	const cursor&	get_cursor() const {
		return c;
	}

	const stack&	get_stack() const {
		return s;
	}

	void 		load_board_from_filename(const std::string& _f) {
		board_loader 	bl;
		b=bl.from_filename(_f);
	}

	void 		step() {

		auto np=b.get_movement_position(c.get_position(), c.get_heading());
		c.set_position(np);

		char val=b.get_tile(np).get_val();
		switch(val) {
			case tile::noop: //Everything's cool...
				break;
			case tile::move_up:		c.set_heading(directions::up); break;
			case tile::move_down:		c.set_heading(directions::down); break;
			case tile::move_right:		c.set_heading(directions::right); break;
			case tile::move_left:		c.set_heading(directions::left); break;
			case tile::addition: 		s.push(s.pop()+s.pop()); break;
			case tile::substraction: 	s.push(s.pop()-s.pop()); break;
			case tile::multiplication: 	s.push(s.pop()*s.pop()); break;
			case tile::division: 		s.push(s.pop()/s.pop()); break;
			case tile::modulo: 		s.push(s.pop()%s.pop()); break;
			default:
				if(std::isdigit(val)) {
					//TODO: No magic numbers...
					s.push({static_cast<register_item::t_stack>(val-48)});
				}
				else {
					s.push({static_cast<register_item::t_stack>(val)});
				}
			break;
		}
	}



	private:

	//TODO: Terrible variable names...
	cursor 		c;
	stack		s;
	board 		b;

};

}

#endif
