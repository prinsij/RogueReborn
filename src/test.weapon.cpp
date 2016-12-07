/**
 * @file test.weapon.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the WeaponTest class
 */ 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "include/playerchar.h"
#include "include/weapon.h"
#include "test.testable.h"

/**
 * @brief      Tests the Weapon class.
 */
class WeaponTest : public Testable {
	public:
		WeaponTest(){}

		void test(){
			comment("Commencing Weapon tests...");

			try {
				Weapon weaponCon = Weapon(Coord(0,0));
				assert(true, "Created Weapon (1)");
				Weapon weaponCon2 = Weapon(Coord(0,0), Item::FLOOR, 0);
				assert(true, "Created Weapon (2)");
			} catch (const std::exception& e) {
				assert(false, "Failure creating Potion");
			}

			Weapon weapon = Weapon(Coord(0,0), Item::FLOOR, 5);
			weapon.setEnchantments(-1, -2);

			assert (weapon.isIdentified(), "Weapon Identification Test");
			assert (weapon.hasEffect(Item::CURSED), "Weapon Curse Test");
			assert (weapon.getName().find("/") != std::string::npos, "Get Weapon Name");
			assert (weapon.getEnchantments() == std::make_pair<int, int>(-1, -2), "Get Weapon Enchantments");

			comment("Finished Weapon tests.");
		}
};
