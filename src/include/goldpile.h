/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: goldpile.h
 */ 

#pragma once

#include "coord.h"
#include "feature.h"

/** Represents a pile of gold on the ground,
 *  which can be picked up by the player to
 *  enhance their score.
 */
class GoldPile : public Feature {
	public:
		/** Constructor of location, quantity. */
		GoldPile(Coord, int);
		/** Getter for quantity.
		 * @see quantity
		 */
		int getQuantity();
	private:
		/** Amount of gold.
		 * Should be positive, non-zero.
		 */
		int quantity;
};
