#include "coord.h"
#include <string>

#ifndef ITEM_H
#define ITEM_H


class Item {
	public:
		enum Location {OnGround, InPack};
		enum Identified {Known, Unknown};
		Coord getCoord();
		std::string getName();	
		Location getLocation();
		Identified isIdentified();
	private:
		Coord coord;
		std::string name;
		Location location;
		Identified knowledge;
};

#endif
