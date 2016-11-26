/**
 * @file food.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the Food class
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "item.h"
#include "playerchar.h"

/**
 * Represents food.
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
		 * @return     A value reflecting the success of the activation operation.
		 */
		bool activate(PlayerChar*);

	private:
		/** Lower bound of food effect */
		int FOOD_LOW = 750;

		/** Middle bound of food effect */
		int FOOD_MIDDLE = 950;

		/** Upper bound of food effect */
		int FOOD_HIGH = 1150;

		/** All food weighs the following value */
		static constexpr int FOOD_WEIGHT = 2;
};
