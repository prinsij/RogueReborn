#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"
#include "mob.h"

// <Name> 
using POTION_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Potion : public Item {
	public:
		static void initializeMap();
		
		Potion(Coord);
		Potion(Coord, Item::Context, int);
		bool activate(Mob*);

	private:
		static std::vector<POTION_TUPLE_TYPE> typeVector;
		static std::vector<std::string> nameVector;
};

std::vector<POTION_TUPLE_TYPE> Potion::typeVector = {
	POTION_TUPLE_TYPE {"Potion of Increase Strength"},
	POTION_TUPLE_TYPE {"Potion of Restore Strength"},
	POTION_TUPLE_TYPE {"Potion of Healing"},
	POTION_TUPLE_TYPE {"Potion of Extra Healing"},
	POTION_TUPLE_TYPE {"Potion of Poison"},
	POTION_TUPLE_TYPE {"Potion of Raise Level"},
	POTION_TUPLE_TYPE {"Potion of Blindness"},
	POTION_TUPLE_TYPE {"Potion of Hallucination"},
	POTION_TUPLE_TYPE {"Potion of Detect Monster"},
	POTION_TUPLE_TYPE {"Potion of Detect Things"},
	POTION_TUPLE_TYPE {"Potion of Confusion"},
	POTION_TUPLE_TYPE {"Potion of Levitation"},
	POTION_TUPLE_TYPE {"Potion of Haste Self"},
	POTION_TUPLE_TYPE {"Potion of See Invisible"}
};

std::vector<std::string> Potion::nameVector = {
	"Blue Potion", "Red Potion", "Green Potion", "Grey Potion", "Brown Potion",
	"Clear Potion", "Pink Potion", "White Potion", "Purple Potion", "Black Potion",
	"Yellow Potion", "Plaid Potion", "Burgundy Potion", "Beige Potion"
};