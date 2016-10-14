#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Mob;

class Potion : public Item {
	public:
		Potion(Coord, Item::Context, std::string, std::string, unsigned char);
		bool activate(Mob*);
};