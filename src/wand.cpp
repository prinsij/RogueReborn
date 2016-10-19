#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/wand.h"

std::vector<WAND_TUPLE_TYPE > Wand::typeVector = {
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

std::vector<std::string> Wand::nameVector = Item::shuffleNameVector({
	"Steel Wand", "Bronze Wand", "Gold Wand", "Silver Wand", "Copper Wand",
	"Nickel Wand", "Cobalt Wand", "Tin Wand", "Iron Wand", "Magnesium Wand",
	"Chrome Wand", "Carbon Wand", "Platinum Wand", "Silicon Wand", "Titanium Wand",
	"Teak Wand", "Oak Wand", "Cherry Wand", "Birch Wand", "Pine Wand",
	"Cedar Wand", "Redwood Wand", "Balsa Wand", "Ivory Wand", "Walnut Wand",
	"Maple Wand", "Mahogany Wand", "Elm Wand", "Palm Wand", "Wooden Wand"
});


Wand::Wand(Coord location)
	: Wand(location, Item::Context::FLOOR, rand() % Wand::typeVector.size()) {}

Wand::Wand(Coord location, Item::Context context, int type)
	: Item('/', location, context, "Wand", std::get<0>(Wand::typeVector[type]), Wand::nameVector[type], type, false, false),
	  charges(3 + (rand() % 5)) {}

bool Wand::activate(Level* level) {
	this->charges--;
	return false;
}

int Wand::getCharges() {
	return this->charges;
}
