#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/scroll.h"

std::vector<bool> Scroll::identified;

Scroll::Scroll(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('*', location, context, name, pseudoName, type, true, false) {

		Item::setIdentified(this->isIdentified(type));
}

void Scroll::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

bool Scroll::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}
