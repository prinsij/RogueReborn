#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/food.h"

std::vector<bool> Food::identified;

Food::Food(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('*', location, context, name, pseudoName, type, true, false) {

		Item::setIdentified(this->isIdentified(type));
}

void Food::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

bool Food::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}