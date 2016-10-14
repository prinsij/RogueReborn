#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

class Armor : public Item {
	public:
		Armor(Coord, Item::Context, std::string, std::string, unsigned char, int);
		void addIdentified(unsigned char);
		int getRating();
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
		int rating;
};