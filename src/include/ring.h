#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Level;

class Ring : public Item {
	public:
		Ring(Coord, Item::Context, std::string, std::string, unsigned char);
		bool activate(Level*);
};