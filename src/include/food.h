#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

class Food : public Item {
	public:
		Food(Coord, Item::Context, std::string, std::string, unsigned char);
		void addIdentified(unsigned char);
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
};