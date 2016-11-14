/**
 * @file potion.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Potion class
 */ 

#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/potion.h"
#include "include/random.h"

std::vector<std::string> Potion::nameVector = Item::shuffleNameVector({
	"Blue Potion", "Red Potion", "Green Potion", "Grey Potion", "Brown Potion",
	"Clear Potion", "Pink Potion", "White Potion", "Purple Potion", "Black Potion",
	"Yellow Potion", "Plaid Potion", "Burgundy Potion", "Beige Potion"
});

std::vector<POTION_TUPLE_TYPE > Potion::typeVector = {
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

Potion::Potion(Coord location)
	: Potion(location, Item::Context::FLOOR, Generator::intFromRange(0, Potion::typeVector.size() - 1)) {}

Potion::Potion(Coord location, Item::Context context, int type)
	: Item('!', location, context, "Potion", std::get<0>(Potion::typeVector[type]), Potion::nameVector[type], type, true, true) {}

bool Potion::activate(Mob* mob) {
	// TODO

	return true;
}