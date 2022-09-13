#ifndef APP_EXCEPTION_H
#define APP_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace app {

class display_size_exception:public std::runtime_error {
	public:
	display_size_exception(const std::string& _m):std::runtime_error(_m) {

	}
};

}


#endif
