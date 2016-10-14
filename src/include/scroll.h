#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Level;

class Scroll : public Item {
	public:
		Scroll(Coord, Item::Context, std::string, std::string, unsigned char);
		bool activate(Level*);
};