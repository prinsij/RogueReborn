#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Armor : public Item {
	public:
		Armor(Coord, Item::Context, std::string, std::string, unsigned char, int);
		int getRating();
	private:
		int rating;
};