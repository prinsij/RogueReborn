#include "include/coord.h"

#include "include/food.h"
#include "include/item.h"

Food::Food(Coord location, Item::Context context)
	: Item(':', location, context, "Food", "Some Rations of Food", 0, true, false) {}

bool Food::activate(PlayerChar* player) {
	// TODO

	return true;
}
