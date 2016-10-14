#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Potion : public Item {
	public:
		Potion(Coord, Item::Context, std::string, std::string, unsigned char);
		void addIdentified(unsigned char);
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
};