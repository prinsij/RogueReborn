#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name, Rating> 
using ARMOR_TUPLE_TYPE = std::tuple<std::string, int>;

class Armor : public Item {
	public:
		Armor(Coord);
		Armor(Coord, Item::Context, int);
		int getRating();

	private:
		static std::vector<ARMOR_TUPLE_TYPE> typeVector;

		int enchantProtection;
		int rating;
};

std::vector<ARMOR_TUPLE_TYPE> Armor::typeVector = {
	ARMOR_TUPLE_TYPE {"Leather Armor", 3},
	ARMOR_TUPLE_TYPE {"Ring Mail", 3},
	ARMOR_TUPLE_TYPE {"Scale Mail", 4},
	ARMOR_TUPLE_TYPE {"Chain Mail", 5},
	ARMOR_TUPLE_TYPE {"Banded Mail", 6},
	ARMOR_TUPLE_TYPE {"Splint Mail", 6},
	ARMOR_TUPLE_TYPE {"Plate Mail", 7}
};