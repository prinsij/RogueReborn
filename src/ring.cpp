#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/ring.h"

std::vector<bool> Ring::identified;

Ring::Ring(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('*', location, context, name, pseudoName, type, false, false) {
		Item::setIdentified(this->isIdentified(type));
}

void Ring::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

bool Ring::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}
