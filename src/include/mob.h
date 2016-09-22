#include "coord.h"
#include <string>

#ifndef MOB_H
#define MOB_H

class Mob {
	public:
		Mob(std::string, Coord);
		Coord getCoord();
		std::string getName();
	private:
		std::string name;
		Coord coord;
};

#endif
