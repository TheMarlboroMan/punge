#pragma once
#include "typedefs.h"
#include "coordinates.h"
#include <vector>
#include <string>
namespace interpreter {

/**
 * board extensions are board metadata which are not needed by the interpreter
 * but are needed for this game. Even if these are in no way part of 
 * Befunge93 they will live in the interpreter namespace, just for ease of
 * use and implementation.
 * This class only serves as a container. Logic will go somewhere else.
 */
struct board_extension {

	bool					extended{false}; //indicates whether or not there's any info in this class.
	std::string				author,
							title,
							expects, //!output that the program expects on termination.
	//characters the user can enter, repeated ones are allowed. if empty
	//it is assumed that there is no limitation.
							allowed_input;
	std::vector<t_stack> 	initial_stack;
	std::vector<coordinates> non_writable_cells; //cells where the user cannot put anything.
};
}
