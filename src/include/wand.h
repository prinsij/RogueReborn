/**
 * @file wand.h
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member declarations for the Wand class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

/** Tuple representing Wand information (<Name>)*/
using WAND_TUPLE_TYPE = std::tuple<std::string>;

class Level;
class Mob;

/**
 * Represents a wand item.
 */
class Wand : public Item {
	public:
		/**
		 * @brief      Constructs a Wand instance with a random type.
		 *
		 * @param[in]  location  Wand location
		 */
		Wand(Coord);

		/**
		 * @brief      Constructs a Wand instance.
		 *
		 * @param[in]  location  Wand location
		 * @param[in]  context  Wand context
		 * @param[in]  type  Wand type
		 */
		Wand(Coord, Item::Context, int);

		/**
		 * @brief      Applies the effects derived from using a zap from this Wand.
		 *
		 * @param      level  Reference to the Level instance
		 * @param      mob Mob to target (NULL for no hit target)
		 *
		 * @return     A value reflecting the success of the activation operation.
		 */
		bool activate(Level*, Mob*);

		/**
		 * @brief      Gets the charges.
		 *
		 * @return     The charges.
		 */
		int getCharges();

	private:
		/**
		 * Vector of tuples representing different Wand configurations indexed by type.
		 */
		static std::vector<WAND_TUPLE_TYPE > typeVector;

		/**
		 * Vector of names to be applied to Wands that are unidentified indexed by type.
		 */
		static std::vector<std::string> nameVector;

		/**
		 * Quantity of remaining Wand charges.
		 */
		int charges;

		/**
		 * All wands weigh the following value
		 */
		 static constexpr int WAND_WEIGHT = 1;
};
