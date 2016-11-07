/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: weapon.h
 */ 

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
		static std::vector<WEAPON_TUPLE_TYPE > typeVector;

		std::pair<int, int> damage;
		int enchantDamage;
		int enchantHit;
		bool melee;
};