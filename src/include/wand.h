#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class Wand : public Item {
	public:
		Wand(Coord, Item::Context, std::string, std::string, unsigned char);
		void addIdentified(unsigned char);
		int getCharges();
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
		int charges;
};