/**
 * @file scroll.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Scroll class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

/** Tuple representing Scroll information (<Name>) */
using SCROLL_TUPLE_TYPE = std::tuple<std::string>;

class Level;

/**
 * Represents scrolls.
 */
class Scroll : public Item {
	public:
		/**
		 * @brief      Initializes the unidentified names of each Scroll.
		 *
		 * @return     Returns a vector of strings denoting random Scroll names indexed by type.
		 */
		static std::vector<std::string> initializeScrollNames();

		/**
		 * @brief      Constructs a Scroll instance with a random type.
		 *
		 * @param[in]  location  Scroll location
		 */
		Scroll(Coord);

		/**
		 * @brief      Constructs a Scroll instance.
		 *
		 * @param[in]  location  Scroll location
		 * @param[in]  context  Scroll context
		 * @param[in]  type  Scroll type
		 */
		Scroll(Coord, Item::Context, int);

		/**
		 * @brief      Applies the effects derived from reading this Scroll.
		 *
		 * @param      level  Reference to the Level instance
		 *
		 * @return     A value reflecting the success of the activation operation.
		 */
		bool activate(Level*);

	private:
		/**
		 * Vector of tuples representing different Scroll configurations indexed by type.
		 */
		static std::vector<SCROLL_TUPLE_TYPE > typeVector;

		/**
		 * Vector of names to be applied to Scrolls that are unidentified indexed by type.
		 */
		static std::vector<std::string> nameVector;

		/**
		 * Vector of syllables to be used when constructing the randomized Scroll names.
		 */
		static std::vector<std::string> syllableVector;
};