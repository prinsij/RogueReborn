#include "include/coord.h"
#include "include/item.h"
#include "include/wand.h"

Wand::Wand(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('/', location, context, "Wand", name, pseudoName, type, false, false),
	  charges(0) {}

bool Wand::activate(Level* level) {
	this->charges--;
	return false;
}

int Wand::getCharges() {
	return this->charges;
}