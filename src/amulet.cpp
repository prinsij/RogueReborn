/**
 * @file amulet.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the Amulet class
 */ 

#include <string>

#include "include/amulet.h"
#include "include/coord.h"
#include "include/item.h"

Amulet::Amulet(Coord location, Item::Context context)
	: Item(',', location, context, "Amulet", "The Amulet of Yendor", 0, false, false) {}
