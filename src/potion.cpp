#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/potion.h"

std::vector<bool> Potion::identified;

Potion::Potion(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('*', location, context, name, pseudoName, type, true, true) {
		
		Item::setIdentified(this->isIdentified(type));
}

void Potion::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

bool Potion::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}