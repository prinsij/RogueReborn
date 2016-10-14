#include "include/coord.h"
#include "include/item.h"
#include "include/scroll.h"

Scroll::Scroll(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item('?', location, context, "Scroll", name, pseudoName, type, true, false) {}

bool Scroll::activate(Level* level) {
	return false;
}