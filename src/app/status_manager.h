#ifndef STATUS_MANAGER_H
#define STATUS_MANAGER_H

namespace app {
//!Manages two variables of a templated type. One of them will be declared as
//!the current value and the other as a future, desired value. Provides an
//!interface to manipulate the values.
template <typename T>
class status_manager {

	public:

	//!Class constructor.
			status_manager(T _value)
		:current(_value), next(_value) {

	}

	//!Gets the current value.
	T		get_current() const {return current;}

	//!Gets the desired value.
	T		get_next() const {return next;}

	//!Requests a change for the current value.
	void		request(T _value) {next=_value;}

	//!Rejects a proposed change for the current value.
	void		reject() {next=current;}

	//!Accepts the change for the current value.
	void		accept() {current=next;}

	//!Returns true if a change has been proposed.
	bool		is_change() const {return next!=current;}

	
	private:

	T		current,
			next;

};
}

#endif
