#ifndef INTERPRETER_STACK_MANIPULATOR_H
#define INTERPRETER_STACK_MANIPULATOR_H

#include "stack.h"

namespace interpreter {

class stack_manipulator {

	public:

	void	add(stack& _s);
	void	substract(stack& _s);
	void	multiply(stack& _s);
	void	divide(stack& _s);
	void	modulo(stack& _s);
	void	duplicate(stack& _s);
	void	swap(stack& _s);
	void	logical_not(stack& _s);
	void	greater_than(stack& _s);
};

}

#endif
