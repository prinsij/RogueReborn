/**
 * @file armor.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Armor class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"


/** Tuple representing Armor information */
using ARMOR_TUPLE_TYPE = std::tuple<std::string, int>;

/**
 * Represents an Armor item.
 */
class Armor : public Item {
	public:
		/**
		 * @brief      Constructs an Armor instance with a random type.
		 *
		 * @param[in]  location  Armor location.
		 */
		Armor(Coord);

		/**
		 * @brief      Constructs an Armor instance.
		 *
		 * @param[in]  location  Armor location
		 * @param[in]  context  Armor context
		 * @param[in]  type  Armor type
		 */
		Armor(Coord, Item::Context, int);

		/**
		 * @brief      Gets the rating.
		 *
		 * @return     The rating.
		 */
		int getRating();

	private:
		/**
		 * Vector of tuples representing different Armor configurations indexed by type.
		 */
		static std::vector<ARMOR_TUPLE_TYPE > typeVector;

		/**
		 * Protection enchantment value.
		 */
		int enchantProtection;

		/**
		 * Protection rating.
		 */
		int rating;
};