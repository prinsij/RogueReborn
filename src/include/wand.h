#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name> 
using WAND_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Wand : public Item {
	public:
		static void initializeMap();
		
		Wand(Coord);
		Wand(Coord, Item::Context, int);
		bool activate(Level*);
		int getCharges();

	private:
		static std::vector<WAND_TUPLE_TYPE > typeVector;
		static std::vector<std::string> nameVector;

		int charges;
};
