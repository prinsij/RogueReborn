#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Projectile : public Item {
	public:
		Projectile(Coord, Item::Context, std::string, unsigned char, std::pair<int, int>);
		int getChance();
		int getDamage();
	private:
		std::pair<int, int> enchantment;
};