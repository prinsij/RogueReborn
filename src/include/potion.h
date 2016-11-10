/**
 * @file potion.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Potion class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"
#include "mob.h"

/** Tuple representing Potion information (<Name>) */
using POTION_TUPLE_TYPE = std::tuple<std::string>;

class Level;

/**
 * Represents a Potion item.
 */
class Potion : public Item {
	public:
		/**
		 * @brief      Constructs a Potion instance with a random type.
		 *
		 * @param[in]  location  Potion location
		 */
		Potion(Coord);

		/**
		 * @brief      Constructs a Potion instance.
		 *
		 * @param[in]  location  Potion location
		 * @param[in]  context  Potion context
		 * @param[in]  type  Potion type
		 */
		Potion(Coord, Item::Context, int);

		/**
		 * @brief      Applies the effects derived from quaffing this Potion. 
		 *
		 * @param      mob  Reference to the Mob instance
		 *
		 * @return     A value reflecting the success of the activation operation.
		 */
		bool activate(Mob*);

	private:
		/**
		 * Vector of tuples representing different Potion configurations indexed by type.
		 */
		static std::vector<POTION_TUPLE_TYPE > typeVector;

		/**
		 * Vector of names to be applied to Potions that are unidentified indexed by type.
		 */
		static std::vector<std::string> nameVector;
};