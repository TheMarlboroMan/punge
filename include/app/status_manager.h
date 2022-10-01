#pragma once
#include <stack>

namespace app {
//!Manages two variables of a templated type. One of them will be declared as
//!the current value and the other as a future, desired value. Provides an
//!interface to manipulate the values.
template <typename T>
class status_manager {

	public:

	//!Class constructor.
			status_manager(T _value)
	{
		stack.push(_value);
	}

	//!Gets the current value.
	T		get_current() const {return stack.top();}
	
	//!Gets the previous value.
	T		get_previous() const {return prev_state;}

	//!Requests a change for the current value.
	void		request(T _value) {

		change=true;
		prev_state=get_current();
		stack.push(_value);
	}

	void        pop() {

		prev_state=stack.top();
		stack.pop();
		change=true;
	}

	void		accept_change() {

		change=false;
	}

	//!Returns true if a change has been proposed.
	bool		is_change() const {
		
		return change;
	}

	bool		empty() const {

		return stack.empty();
	}


	private:

	std::stack<T>	stack;
	T 				prev_state{};
	bool 			change{false};
};
}

