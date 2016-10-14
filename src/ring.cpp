#include "include/coord.h"
#include "include/item.h"
#include "include/ring.h"

Ring::Ring(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('0', location, context, "Ring", name, pseudoName, type, false, false) {}

bool Ring::activate(Level* level) {
	return false;
}