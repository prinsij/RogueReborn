/**
 * @file armor.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the Armor class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"
#include "saving.h"

/** Tuple representing Armor information (<Name, Rating>)*/
using ARMOR_TUPLE_TYPE = std::tuple<std::string, int>;

/**
 * Represents armor.
 */
class Armor : public Item {
	public:
		/**
		 * @brief      Constructs an Armor instance with a random type.
		 *
		 * @param[in]  location  Armor location
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
		 * @brief      Gets the enchantment.
		 *
		 * @return     The enchantment.
		 */
		int getEnchantment();

		/**
		 * @brief      Gets the rating.
		 *
		 * @return     The rating.
		 */
		int getRating();

		/**
		 * @brief      Sets this Armor's enchantment.
		 *
		 * @param[in]  enchantment New enchantment for this Armor.
		 */
		void setEnchantment(int);

		friend std::string encode(PlayerChar*, Level*);
		friend std::tuple<PlayerChar*, Level*> decode(std::string);

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

		/** All armor weighs the following value */
		static constexpr int ARMOR_WEIGHT = 7;
};
