/**
 * @file test.monster.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/monster.h"
#include "include/playerchar.h"
#include "test.testable.h"

class MonsterTest : public Testable {
	public:
		MonsterTest(){}

		void test(){
			comment("Commencing Monster tests...");

			Monster monster = Monster('B', Coord(0,0));
			assert(true, "Created Monster");

			monster.awake = false;
			monster.chasing = false;
			monster.visible = true;

			monster.addFlag(Monster::INVISIBLE);
			assert(monster.hasFlag(Monster::INVISIBLE), "Monster Flag Add");
			assert(!monster.isVisible(), "Monster Visible Check");

			monster.aggrevate();
			assert(monster.awake && monster.chasing, "Aggravate Check");
			assert(monster.calculateDamage() >= 1, "Damage Check");

			PlayerChar* player = new PlayerChar(Coord(0,0), "Monster Test");

			int hitChance = monster.calculateHitChance(player);

			assert(hitChance >= 1 && hitChance <= 100, "Hit Chance Check");
			assert(monster.getArmorRating() >= -5 && monster.getArmorRating() <= 15, "Armor Rating Check");

			assert(monster.getName(player) == "Something", "Monster Name Check 1");
			monster.removeFlag(Monster::INVISIBLE);
			assert(monster.getName(player) == "Bat", "Monster Name Check 2");

			assert(monster.getSymbolsForLevel(0).size() > 1, "Monster Symbol Level Check");
			assert(monster.getSymbolsForTreasure(0).size() > 1, "Monster Treasure Level Check");

			delete player;

			comment("Finished Monster tests.");
		}
};
