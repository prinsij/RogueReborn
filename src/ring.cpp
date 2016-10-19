#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/ring.h"

void Ring::initializeMap() {
	std::random_shuffle(Ring::nameVector.begin(), Ring::nameVector.end());
}

Ring::Ring(Coord location)
	: Ring(location, Item::Context::FLOOR, rand() % Ring::typeVector.size()) {}

Ring::Ring(Coord location, Item::Context context, int type)
	: Item('=', location, context, "Ring", std::get<0>(Ring::typeVector[type]), Ring::nameVector[type], type, true, true) {}

bool Ring::activate(Level* level) {
	// TODO

	return true;
}