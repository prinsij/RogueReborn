#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Weapon : public Item {
	public:
		Weapon(Coord, Item::Context, std::string, std::string, unsigned char, std::pair<int, int>, bool, bool);
		int getChance();
		int getDamage();
		bool isMelee();

	private:
		std::pair<int,int> enchantment;
		bool melee;
};