#pragma once

#include <string>

#include "coord.h"
#include "item.h"

// <Name> 
using RING_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Ring : public Item {
	public:
		static void initializeMap();

		Ring(Coord);
		Ring(Coord, Item::Context, int);
		bool activate(Level*);

	private:
		static std::vector<RING_TUPLE_TYPE > typeVector;
		static std::vector<std::string> nameVector;
};

