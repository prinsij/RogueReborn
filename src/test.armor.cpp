/**
 * @file test.armor.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/playerchar.h"
#include "test.testable.h"

class ArmorTest : public Testable {
	public:
		ArmorTest(){}

		void test(){
			comment("Commencing Armor tests...");

			Armor armorCon = Armor(Coord(0,0));
			assert(true, "Created Armor (1)");
			Armor armorCon2 = Armor(Coord(0,0), Item::FLOOR, 0);
			assert(true, "Created Armor (2)");

			Armor armor = Armor(Coord(0,0), Item::FLOOR, 1);
			armor.setEnchantment(-4);

			assert (armor.isIdentified(), "Armor Identification Test");
			assert (armor.hasEffect(Item::CURSED), "Armor Curse Test");
			assert (armor.getEnchantment() == -4, "Get Armor Enchantment");
			assert (armor.getRating() == 3 - 4, "Get Armor Rating");

			comment("Finished Armor tests.");
		}
};
