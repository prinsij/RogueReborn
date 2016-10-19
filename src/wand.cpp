#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/wand.h"

void Wand::initializeMap() {
	std::random_shuffle(Wand::nameVector.begin(), Wand::nameVector.end());
}

Wand::Wand(Coord location)
	: Wand(location, Item::Context::FLOOR, rand() % Wand::typeVector.size()) {}

Wand::Wand(Coord location, Item::Context context, int type)
	: Item('/', location, context, "Wand", std::get<0>(Wand::typeVector[type]), Wand::nameVector[type], type, false, false),
	  charges(3 + (rand() % 5)) {}

bool Wand::activate(Level* level) {
	// TODO

	return true;
}

int Wand::getCharges() {
	return this->charges;
}