#include "include/coord.h"
#include "include/item.h"
#include "include/food.h"

Food::Food(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item(':', location, context, "Food", name, pseudoName, type, true, false) {}

bool Food::activate(PlayerChar* player) {
	// TODO

	return true;
}