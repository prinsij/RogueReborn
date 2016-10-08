#include "coord.h"
#include "feature.h"
#include <string>

#ifndef ITEM_H
#define ITEM_H


class Item : public Feature {
	public:
		enum Location {OnGround, InPack};
		enum Identified {Known, Unknown};
		Item(char, Location, Identified, Coord, std::string);
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
