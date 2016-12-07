/**
 * @file test.wand.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/monster.h"
#include "include/playerchar.h"
#include "include/wand.h"
#include "test.testable.h"

class WandTest : public Testable {
	public:
		WandTest(){}

		void test(){
			comment("Commencing Wand tests...");

			Wand wandCon = Wand(Coord(0,0));
			assert(true, "Created Wand (1)");
			Wand wandCon2 = Wand(Coord(0,0), Item::FLOOR, 0);
			assert(true, "Created Wand (2)");

			std::vector<Wand> wands;
			std::vector<Monster> monsters;

			for (int i = 0 ; i < 11 ; ++i) {
				wands.push_back(Wand(Coord(0,0), Item::FLOOR, i));
				monsters.push_back(Monster('B', Coord(1,0)));
			}

			PlayerChar player = PlayerChar(Coord(0,0), "Wand Test");
			Level level = Level(3, &player);
			level.clear();

			wands[0].activate(&level, &monsters[0]);
			assert (monsters[0].getLocation().distanceTo(player.getLocation()) >= 20, "Wand of Teleport Away");

			wands[1].activate(&level, &monsters[1]);
			assert (monsters[1].hasFlag(Monster::SLOWED), "Wand of Slow Monster");

			wands[2].activate(&level, &monsters[2]);
			assert (monsters[2].hasFlag(Monster::INVISIBLE), "Wand of Invisibility");

			level.registerMob(&monsters[3]);
			wands[3].activate(&level, &monsters[3]);
			assert (level.monsterAt(Coord(1,0)), "Wand of Polymorph");

			wands[4].activate(&level, &monsters[4]);
			assert (monsters[4].hasFlag(Monster::HASTED), "Wand of Haste Monster");

			int hp5 = monsters[5].getHP();
			wands[5].activate(&level, &monsters[5]);
			assert (monsters[5].getHP() < hp5, "Wand of Magic Missile");

			wands[6].activate(&level, &monsters[6]);
			assert (monsters[6].hasFlag(Monster::CANCELLED), "Wand of Cancellation");

			wands[7].activate(&level, &monsters[7]);
			assert (true, "Wand of Do Nothing");

			int playerHP8 = player.getHP();
			int monstersHP8 = monsters[8].getHP();
			wands[8].activate(&level, &monsters[8]);
			assert (player.getHP() < playerHP8 && monsters[8].getHP() < monstersHP8, "Wand of Drain Life");

			wands[9].activate(&level, &monsters[9]);
			assert (true, "Wand of Cold");

			wands[10].activate(&level, &monsters[10]);
			assert (true, "Wand of Fire");


			comment("Finished Wand tests.");
		}
};
