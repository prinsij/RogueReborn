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
		static std::vector<WAND_TUPLE_TYPE> typeVector;
		static std::vector<std::string> nameVector;

		int charges;
};

std::vector<WAND_TUPLE_TYPE> Wand::typeVector = {
	WAND_TUPLE_TYPE {"Wand of Teleport Away"},
	WAND_TUPLE_TYPE {"Wand of Slow Monster"},
	WAND_TUPLE_TYPE {"Wand of Invisibility"},
	WAND_TUPLE_TYPE {"Wand of Polymorph"},
	WAND_TUPLE_TYPE {"Wand of Haste Monster"},
	WAND_TUPLE_TYPE {"Wand of Magic Missile"},
	WAND_TUPLE_TYPE {"Wand of Cancellation"},
	WAND_TUPLE_TYPE {"Wand of Do Nothing"},
	WAND_TUPLE_TYPE {"Wand of Drain Life"},
	WAND_TUPLE_TYPE {"Wand of Cold"},
	WAND_TUPLE_TYPE {"Wand of Fire"}
};

std::vector<std::string> Wand::nameVector = {
	"Steel Wand", "Bronze Wand", "Gold Wand", "Silver Wand", "Copper Wand",
	"Nickel Wand", "Cobalt Wand", "Tin Wand", "Iron Wand", "Magnesium Wand",
	"Chrome Wand", "Carbon Wand", "Platinum Wand", "Silicon Wand", "Titanium Wand",
	"Teak Wand", "Oak Wand", "Cherry Wand", "Birch Wand", "Pine Wand",
	"Cedar Wand", "Redwood Wand", "Balsa Wand", "Ivory Wand", "Walnut Wand",
	"Maple Wand", "Mahogany Wand", "Elm Wand", "Palm Wand", "Wooden Wand"
};