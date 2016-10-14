#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

class Ring : public Item {
	public:
		Ring(Coord, Item::Context, std::string, std::string, unsigned char);
		void addIdentified(unsigned char);
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
};