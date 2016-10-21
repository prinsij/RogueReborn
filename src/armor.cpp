#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"


std::vector<ARMOR_TUPLE_TYPE > Armor::typeVector = {
	ARMOR_TUPLE_TYPE {"Leather Armor", 3},
	ARMOR_TUPLE_TYPE {"Ring Mail", 3},
	ARMOR_TUPLE_TYPE {"Scale Mail", 4},
	ARMOR_TUPLE_TYPE {"Chain Mail", 5},
	ARMOR_TUPLE_TYPE {"Banded Mail", 6},
	ARMOR_TUPLE_TYPE {"Splint Mail", 6},
	ARMOR_TUPLE_TYPE {"Plate Mail", 7}
};

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
