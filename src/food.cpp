#include "include/coord.h"
<<<<<<< HEAD
#include "include/item.h"
#include "include/food.h"

Food::Food(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type)
	: Item(':', location, context, "Food", name, pseudoName, type, true, false) {}
=======
#include "include/food.h"
#include "include/item.h"

Food::Food(Coord location, Item::Context context)
	: Item(':', location, context, "Food", "Some Rations of Food", 0, true, false) {}
>>>>>>> LinkTest

bool Food::activate(PlayerChar* player) {
	// TODO

	return true;
}