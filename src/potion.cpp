#include "include/coord.h"
#include "include/item.h"
#include "include/potion.h"

Potion::Potion(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('!', location, context, "Potion", name, pseudoName, type, true, true) {}

bool Potion::activate(Mob* mob) {
	// TODO

	return true;
}