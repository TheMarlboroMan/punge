#include "interpreter/board_extension.h"

using namespace interpreter;

void board_extension::reset() {

	extended=false;
	author.clear();
	title.clear();
	expects.clear();
	allowed_input.clear();
	initial_stack.clear();
	non_writable_cells.clear();
}
