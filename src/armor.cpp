#include <algorithm>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"

std::vector<bool> Armor::identified;

Armor::Armor(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, int rating)
	: Item('*', location, context, name, pseudoName, type, false, false),
	  rating(rating) {

		Item::setIdentified(this->isIdentified(type));
}

void Armor::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

int Armor::getRating() {
	return this->rating;
}

bool Armor::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}