#ifndef TILE_H
#define TILE_H

namespace app {

class tile {

	public:

	static const char space='a';

			tile(char _v):val{_v}{

	};

	char		get_val() const {return val;}

	private:

	char		val;

};

}

#endif
