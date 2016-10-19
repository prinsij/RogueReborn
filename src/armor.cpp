#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"

Armor::Armor(Coord location)
	: Armor(location, Item::Context::FLOOR, rand() % Armor::typeVector.size()) {}

Armor::Armor(Coord location, Item::Context context, int type)
	: Item(']', location, context, "Armor", std::get<0>(Armor::typeVector[type]), type, false, false),
	  rating(std::get<1>(Armor::typeVector[type])) {

	  	this->enchantProtection = (rand() % 3) - 1;
	}

int Armor::getRating() {
	return this->rating + this->enchantProtection;
}
