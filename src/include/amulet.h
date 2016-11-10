/**
 * @file amulet.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Amulet class
 */ 

#pragma once

#include "coord.h"
#include "item.h"

/**
 * Represents the Amulet of Yendor.
 */
class Amulet : public Item {
	public:
		/**
		 * Constructor that accepts a location and a position context.
		 */
		Amulet(Coord, Item::Context);
};