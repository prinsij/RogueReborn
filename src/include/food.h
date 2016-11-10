/**
 * @file food.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Food class
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class PlayerChar;

/**
 * Represents a Food item.
 */
class Food : public Item {
	public:
		/**
		 * @brief      Constructs a Food instance.
		 *
		 * @param[in]  location  Food location
		 * @param[in]  context  Food context
		 */
		Food(Coord, Item::Context);

		/**
		 * @brief      Applies the effects derived from eating this Food. 
		 *
		 * @param      player  Reference to the PlayerCharacter instance
		 *
		 * @return     'true' if the Food effect was successfully applied; otherwise, 'false'.
		 */
		bool activate(PlayerChar*);
};