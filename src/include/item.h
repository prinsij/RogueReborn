#include "coord.h"
#include <string>

class Item {
	public:
		static const enum Location {OnGround, InPack};
		static const enum Identified {Known, Unknown};
		Coord getCoord();
		std::string getName();	
		Location getLocation();
		Identified isIdentified();
	private:
		Coord coord;
		std::string name;
		Location location;
		Identified knowledge;
}
