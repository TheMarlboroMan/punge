#include "stack_manipulator.h"

using namespace interpreter;

void stack_manipulator::add(stack& _s) {

	_s.push(_s.pop()+_s.pop());
}

void stack_manipulator::substract(stack& _s) {

	_s.push(_s.pop()-_s.pop());
}

void stack_manipulator::multiply(stack& _s) {

	_s.push(_s.pop()*_s.pop());
}

void stack_manipulator::divide(stack& _s) {

	_s.push(_s.pop()/_s.pop());
}

void stack_manipulator::modulo(stack& _s) {

	_s.push(_s.pop()%_s.pop());
}

void stack_manipulator::duplicate(stack& _s) {

	auto item=_s.pop();
	_s.push(item);
	_s.push(item);
}

void stack_manipulator::swap(stack& _s) {

	auto a=_s.pop(), b=_s.pop();
	_s.push(a);
	_s.push(b);
}

void stack_manipulator::logical_not(stack& _s) {

	auto val=_s.pop();
	_s.push(!val.value ? register_item{1} : register_item{0});
}

void stack_manipulator::greater_than(stack& _s) {

	auto a=_s.pop(), b=_s.pop();
	_s.push(b > a ? register_item{1} : register_item{0});
}
