#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name, Damage, Melee, Stackable>
using WEAPON_TUPLE_TYPE = std::tuple<std::string, std::pair<int, int>, bool, bool>;

class Weapon : public Item {
	public:
		Weapon(Coord);
		Weapon(Coord, Item::Context, int);
		int getChance();
		std::tuple<int, int, int> getDamage();
		bool isMelee();

	private:
		static std::vector<WEAPON_TUPLE_TYPE> typeVector;

		std::pair<int, int> damage;
		int enchantDamage;
		int enchantHit;
		bool melee;
};

std::vector<WEAPON_TUPLE_TYPE> Weapon::typeVector = {
	WEAPON_TUPLE_TYPE {"Short Bow", std::make_pair(0, 0), false, false},
	WEAPON_TUPLE_TYPE {"Darts", std::make_pair(1, 1), true, true},
	WEAPON_TUPLE_TYPE {"Arrows", std::make_pair(1, 2), true, true},
	WEAPON_TUPLE_TYPE {"Daggers", std::make_pair(1, 3), true, true},
	WEAPON_TUPLE_TYPE {"Shurikens", std::make_pair(1, 4), true, true},
	WEAPON_TUPLE_TYPE {"Mace", std::make_pair(2, 3), true, false},
	WEAPON_TUPLE_TYPE {"Long Sword", std::make_pair(3, 4), true, false},
	WEAPON_TUPLE_TYPE {"Two-Handed Sword", std::make_pair(4, 5), true, false}
};