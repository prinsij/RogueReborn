/**
 * @file test.trap.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the TrapTest class
 */ 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/level.h"
#include "include/playerchar.h"
#include "include/trap.h"
#include "test.testable.h"

/**
 * @brief      Tests the Trap class.
 */
class TrapTest : public Testable {
	public:
		TrapTest(){}

		void test(){
			comment("Commencing Trap tests...");

			try {
				Trap trapCon = Trap(Coord(0,0), 0, false);
				assert(true, "Created Trap");
			} catch (const std::exception& e) {
				assert(false, "Failure creating Trap");
			}

			std::vector<Trap> traps;

			for (int i = 0 ; i < 6 ; ++i) {
				traps.push_back(Trap(Coord(0,0), i, true));
			}

			PlayerChar* player = new PlayerChar(Coord(0,0), "Player Trap");
			player->setDexterity(-5);

			Level* level = new Level(1, player);
			level->clear();
			level->registerMob(player);

			Armor* armor = new Armor(Coord(0,0), Item::FLOOR, 1);
			armor->setEnchantment(1);
			player->equipArmor(armor);

			level = traps[0].activate(player, level);
			assert(level->getDepth() == 2, "Door Trap");
			level->clear();

			traps[1].activate(player, level);
			assert(armor->getEnchantment() == 0, "Rust Trap");

			traps[2].activate(player, level);
			assert(player->hasCondition(PlayerChar::SLEEPING), "Sleep Trap");
			player->clearConditions();
			player->setCurrentHP(10);

			traps[3].activate(player, level);
			assert(player->hasCondition(PlayerChar::IMMOBILIZED), "Bear Trap");
			player->clearConditions();
			player->setCurrentHP(10);

			Coord position = player->getLocation();
			traps[4].activate(player, level);
			assert(position != player->getLocation(), "Teleport Trap");

			int playerHP = player->getHP();
			traps[5].activate(player, level);
			int deltaHP = playerHP - player->getHP();
			assert(deltaHP >= 1 && deltaHP <= 6, "Dart Trap");

			comment("Finished Trap tests.");
		}
};
