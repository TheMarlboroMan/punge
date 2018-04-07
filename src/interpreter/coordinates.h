#ifndef INTERPRETER_COORDINATES_H
#define INTERPRETER_COORDINATES_H

namespace interpreter {

struct coordinates {
	int x, y;
	coordinates(int _x, int _y):x(_x), y(_y) {}
	coordinates():x(0), y(0) {}
};

}

#endif
