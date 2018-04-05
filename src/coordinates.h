#ifndef COORDINATES_H
#define COORDINATES_H

namespace app {

struct coordinates {
	int x, y;
	coordinates(int _x, int _y):x(_x), y(_y) {}
	coordinates():x(0), y(0) {}
};

}

#endif
