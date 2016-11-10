/**
 * @file ring.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Ring class
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "item.h"

/** Tuple representing Ring information (<Name>) */
using RING_TUPLE_TYPE = std::tuple<std::string>;

class Level;

/**
 * Represents a Ring item.
 */
class Ring : public Item {
	public:
		/**
		 * @brief      Constructs a Ring instance with a random type.
		 *
		 * @param[in]  location  Ring location
		 */
		Ring(Coord);

		/**
		 * @brief      Constructs a Ring instance.
		 *
		 * @param[in]  location  Ring location
		 * @param[in]  context  Ring context
		 * @param[in]  type  Ring type
		 */
		Ring(Coord, Item::Context, int);

		/**
		 * @brief      Applies the effects derived from equipping this Ring. 
		 *
		 * @param      level  Reference to the Level instance
		 *
		 * @return     A value reflecting the success of the activation operation.
		 */
		bool activate(Level*);

	private:
		/**
		 * Vector of tuples representing different Ring configurations indexed by type.
		 */
		static std::vector<RING_TUPLE_TYPE > typeVector;

		/**
		 * Vector of names to be applied to Rings that are unidentified indexed by type.
		 */
		static std::vector<std::string> nameVector;
};