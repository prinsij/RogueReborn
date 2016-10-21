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
		static std::vector<ARMOR_TUPLE_TYPE > typeVector;

		int enchantProtection;
		int rating;
};
