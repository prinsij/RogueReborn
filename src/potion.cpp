#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/potion.h"

void Potion::initializeMap() {
	std::random_shuffle(Potion::nameVector.begin(), Potion::nameVector.end());
}

Potion::Potion(Coord location)
	: Potion(location, Item::Context::FLOOR, rand() % Potion::typeVector.size()) {}

Potion::Potion(Coord location, Item::Context context, int type)
	: Item('!', location, context, "Potion", std::get<0>(Potion::typeVector[type]), Potion::nameVector[type], type, true, true) {}

bool Potion::activate(Mob* mob) {
	// TODO

	return true;
}