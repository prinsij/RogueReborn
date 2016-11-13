/**
 * @file armor.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Armor class
 */ 

#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"
#include "include/random.h"

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
	: Armor(location, Item::Context::FLOOR, Generator::intFromRange(0, Armor::typeVector.size() - 1)) {}

Armor::Armor(Coord location, Item::Context context, int type)
	: Item(']', location, context, "Armor", std::get<0>(Armor::typeVector[type]), type, false, false),
	  rating(std::get<1>(Armor::typeVector[type])) {
		int chance = Generator::intFromRange(1, 100);

		if (chance <= 16) {
			this->cursed = true;
			this->enchantProtection -= Generator::intFromRange(0, 3);
		} else if (chance <= 33) {
			this->enchantProtection += Generator::intFromRange(0, 3);
		}
	}

int Armor::getRating() {
	return this->rating + this->enchantProtection;
}