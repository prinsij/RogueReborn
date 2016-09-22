#include "coord.h"
#include <string>

#ifndef ITEM_H
#define ITEM_H


class Item {
	public:
		enum Location {OnGround, InPack};
		enum Identified {Known, Unknown};
		Item(Location, Identified, Coord, std::string);
		Coord getCoord();
		std::string getName();	
		Location getLocation();
		Identified isIdentified();
		bool operator==(const Item&) const;
	private:
		Location location;
		Identified knowledge;
		Coord coord;
		std::string name;
};

#endif
