#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"

Armor::Armor(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, int rating)
	: Item('(', location, context, "Armor", name, pseudoName, type, false, false),
	  rating(rating) {}

int Armor::getRating() {
	return this->rating;
}