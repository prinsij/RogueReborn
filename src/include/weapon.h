/**
 * @file weapon.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Weapon class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

/**
 * Tuple representing Weapon information (<Name, Damage, Melee, Stackable>)
 */
using WEAPON_TUPLE_TYPE = std::tuple<std::string, std::pair<int, int>, bool, bool>;

/**
 * Represents weapons.
 */
class Weapon : public Item {
	public:
		/**
		 * @brief      Constructs a Weapon instance with a random type.
		 *
		 * @param[in]  location  Weapon location
		 */
		Weapon(Coord);

		/**
		 * @brief      Constructs a Weapon instance.
		 *
		 * @param[in]  location  Weapon location
		 * @param[in]  context  Weapon context
		 * @param[in]  type  Weapon type
		 */
		Weapon(Coord, Item::Context, int);

		/**
		 * @brief      Gets the chance of applying a successful hit.
		 *
		 * @return     The chance of applying a successful hit.
		 */
		int getChance();

		/**
		 * @brief      Gets the damage triple corresponding to this Weapon.
		 *
		 * @return     The tuple <Dice Rolls, Dice Value, Enchantment>.
		 */
		std::tuple<int, int, int> getDamage();

		/**
		 * @brief      Gets the enchantments.
		 *
		 * @return     The enchantments.
		 */
		std::pair<int,int> getEnchantments();

		/**
		 * @brief      Determines if this Weapon is a melee weapon.
		 *
		 * @return     True if melee, False otherwise.
		 */
		bool isMelee();

		/**
		 * @brief	Sets this Weapon's enchantments.
		 *
		 * @param	enchantHit Hit enchantment
		 * @param	enchantDamage Damage enchantment
		 */
		void setEnchantments(int, int);

	private:
		/**
		 * Vector of tuples representing different Weapon configurations indexed by type.
		 */
		static std::vector<WEAPON_TUPLE_TYPE > typeVector;

		/**
		 * @brief	Updates this Weapon's name.
		 */
		void updateName();

		/**
		 * <Dice Rolls, Dice Value> pair representing the damage output of this Weapon.
		 */
		std::pair<int, int> damage;

		/**
		 * Damage enchantment on this Weapon.
		 */
		int enchantDamage;

		/**
		 * Hit enchantment on this Weapon.
		 */
		int enchantHit;

		/**
		 * Denotes whether or not this is a melee Weapon.
		 */
		bool melee;
};