#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name> 
using SCROLL_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Scroll : public Item {
	public:
		static void initializeMap();

		Scroll(Coord);
		Scroll(Coord, Item::Context, int);
		bool activate(Level*);

	private:
		static std::vector<SCROLL_TUPLE_TYPE > typeVector;
		static std::vector<std::string> nameVector;
		static std::vector<std::string> syllableVector;
};

