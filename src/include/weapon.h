#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Weapon : public Item {
	public:
		Weapon(Coord, Item::Context, std::string, std::string, unsigned char, std::pair<int, int>, bool, bool);
		void addIdentified(unsigned char);
		int getChance();
		int getDamage();
		bool isIdentified(unsigned char);
		bool isMelee();

	private:
		static std::vector<bool> identified;
		std::pair<int,int> enchantment;
		bool melee;
};