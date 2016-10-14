#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

class Scroll : public Item {
	public:
		Scroll(Coord, Item::Context, std::string, std::string, unsigned char);
		void addIdentified(unsigned char);
		bool isIdentified(unsigned char);
	private:
		static std::vector<bool> identified;
};