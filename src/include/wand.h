#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Level;

class Wand : public Item {
	public:
		Wand(Coord, Item::Context, std::string, std::string, unsigned char);
		bool activate(Level*);
		int getCharges();
	private:
		int charges;
};