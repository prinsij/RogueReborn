#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/wand.h"

std::vector<bool> Wand::identified;

Wand::Wand(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('*', location, context, name, pseudoName, type, false, false),
	  charges(0) {

		Item::setIdentified(this->isIdentified(type));
}

void Wand::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

int Wand::getCharges() {
	return this->charges;
}

bool Wand::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}