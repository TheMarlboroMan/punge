#pragma once

namespace interpreter {
//TODO: should maybe be unsigned???
struct coordinates {
	int x, y;
	coordinates(int _x, int _y):x(_x), y(_y) {}
	coordinates():x(0), y(0) {}
};

}

