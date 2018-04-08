#ifndef INTERPRETER_STACK_MANIPULATOR_H
#define INTERPRETER_STACK_MANIPULATOR_H

#include "stack.h"

namespace interpreter {

class stack_manipulator {

	public:

	void	add(stack& _s) {
		_s.push(_s.pop()+_s.pop());
	}

	void	substract(stack& _s) {
		_s.push(_s.pop()-_s.pop());
	}

	void	multiply(stack& _s) {
		_s.push(_s.pop()*_s.pop());
	}

	void	divide(stack& _s) {
		_s.push(_s.pop()/_s.pop());
	}

	void	modulo(stack& _s) {
		_s.push(_s.pop()%_s.pop());
	}

	void	duplicate(stack& _s) {
		auto item=_s.pop();
		_s.push(item);
		_s.push(item);
	}

	void	swap(stack& _s) {
		auto a=_s.pop(), b=_s.pop();
		_s.push(a);
		_s.push(b);
	}

	void	logical_not(stack& _s) {
		auto val=_s.pop();
		_s.push(!val.value ? register_item{1} : register_item{0});
	}

	void	greater_than(stack& _s) {
		auto a=_s.pop(), b=_s.pop();
		_s.push(b > a ? register_item{1} : register_item{0});
	}
};

}

#endif
