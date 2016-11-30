/**
 * @file test.mob->cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/mob.h"
#include "include/monster.h"
#include "test.testable.h"

class MobTest : public Testable {
	public:
		MobTest(){}

		void test(){
			comment("Commencing Mob tests...");

			Mob* mob = new Monster('B', Coord(0,0));
			mob->armor = 5;
			mob->currentHP = 20;
			mob->exp = 10;
			mob->level = 2;
			mob->maxHP = 20;
			mob->name = "name";
			assert(true, "Created Mob");
			
			assert(Mob::diceSum(1, 1) == 1, "Dice Sum Check 1");
			assert(Mob::diceSum(2, 1) == 2, "Dice Sum Check 2");
			assert(Mob::diceSum(1, 2) >= 1 && Mob::diceSum(1, 2) <= 2, "Dice Sum Check 3");
			assert(Mob::diceSum(3, 4) >= 3 && Mob::diceSum(3, 4) <= 12, "Dice Sum Check 4");

			assert(mob->getArmorRating() >= -5 && mob->getArmorRating() <= 15, "Mob Armor Check");
			assert(mob->getHP() == 20, "Mob HP Check 1");
			assert(mob->getMaxHP() == 20, "Mob Max HP Check");
			assert(mob->getLevel() == 2, "Mob Level Check");
			assert(mob->getLocation() == Coord(0,0), "Mob Location Check");
			assert(mob->getName() == "name", "Mob Location Check");
			assert(mob->getSymbol() == 'B', "Mob Symbol Check");

			mob->setMaxHP(50);
			assert(mob->getMaxHP() == 50, "Mob Set Max HP Check");
			mob->setCurrentHP(25);
			assert(mob->getHP() == 25, "Mob Set Current HP Check");

			assert(!mob->isDead(), "Mob Dead Check 1");
			mob->setCurrentHP(1);
			mob->hit(5);
			assert(mob->getHP() <= 0, "Mob HP Check 2");
			assert(mob->isDead(), "Mob Dead Check 2");

			delete mob;

			comment("Finished Mob tests.");
		}
};
