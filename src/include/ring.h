/**
 * @file ring.h
 * @author Team Rogue++
 * @date December 06, 2016
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
class RingTest;

/**
 * Represents rings.
 */
class Ring : public Item {
	friend RingTest;

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
		 * @param      player  Reference to the PlayerChar instance
		 *
		 * @return	True if the operation was successful, False otherwise.
		 */
		bool activate(PlayerChar*);

		/**
		 * @brief	Deactivates this Ring's effects on the PlayerChar.
		 *
		 * @param	player Reference to the player
		 *
		 * @return	True if the operation was successful, False otherwise.
		 */
		bool deactivate(PlayerChar*);

	private:
		/**
		 * Vector of tuples representing different Ring configurations indexed by type.
		 */
		static std::vector<RING_TUPLE_TYPE > typeVector;

		/**
		 * Vector of names to be applied to Rings that are unidentified indexed by type.
		 */
		static std::vector<std::string> nameVector;

		/** Arbitrary value for determining dexterity and cursedness */
		int ringValue;

		/** All rings weigh the following value */
		static constexpr int RING_WEIGHT = 1;
};
