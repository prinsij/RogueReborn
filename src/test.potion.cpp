/**
 * @file test.potion.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/playerchar.h"
#include "include/potion.h"
#include "test.testable.h"

class PotionTest : public Testable {
	public:
		PotionTest(){}

		void test(){
			comment("Commencing Potion tests...");

			Potion potionCon = Potion(Coord(0,0));
			assert(true, "Created Potion (1)");
			Potion potionCon2 = Potion(Coord(0,0), Item::FLOOR, 0);
			assert(true, "Created Potion (2)");

			std::vector<Potion> potions;
			std::vector<PlayerChar> players;

			for (int i = 0 ; i < 14 ; i ++) {
				potions.push_back(Potion(Coord(0,0), Item::FLOOR, i));
				players.push_back(PlayerChar(Coord(0,0), "Player Potion " + std::to_string(i)));
			}

			int strength0 = players[0].getStrength();
			potions[0].activate(&players[0]);
			assert (players[0].getStrength() == strength0 + 1, "Potion of Strength");

			int strength1 = players[1].getStrength();
			players[1].changeCurrentStrength(-2);
			potions[1].activate(&players[1]);
			assert (players[1].getStrength() == strength1, "Potion of Restore Strength");

			int maxHP2 = players[2].getMaxHP();
			potions[2].activate(&players[2]);
			assert (players[2].getMaxHP() == maxHP2 + 1, "Potion of Healing");

			int maxHP3 = players[3].getMaxHP();
			potions[3].activate(&players[3]);
			assert (players[3].getMaxHP() == maxHP3 + 2, "Potion of Extra Healing");

			int strength4 = players[4].getStrength();
			potions[4].activate(&players[4]);
			int deltaStrength4 = strength4 - players[4].getStrength();
			assert (deltaStrength4 >= 1 && deltaStrength4 <= 3, "Potion of Poison");

			int level5 = players[5].getLevel();
			potions[5].activate(&players[5]);
			assert (players[5].getLevel() == level5 + 1, "Potion of Raise Level");

			potions[6].activate(&players[6]);
			assert (players[6].hasCondition(PlayerChar::BLIND), "Potion of Blindness");

			potions[7].activate(&players[7]);
			assert (players[7].hasCondition(PlayerChar::HALLUCINATING), "Potion of Hallucination");

			potions[8].activate(&players[8]);
			assert (players[8].hasCondition(PlayerChar::DETECT_MONSTER), "Potion of Detect Monster");

			potions[9].activate(&players[9]);
			assert (players[9].hasCondition(PlayerChar::DETECT_OBJECTS), "Potion of Detect Objects");

			potions[10].activate(&players[10]);
			assert (players[10].hasCondition(PlayerChar::CONFUSED), "Potion of Confusion");

			potions[11].activate(&players[11]);
			assert (players[11].hasCondition(PlayerChar::LEVITATING), "Potion of Levitation");

			potions[12].activate(&players[12]);
			assert (players[12].hasCondition(PlayerChar::HASTED), "Potion of Haste");

			potions[13].activate(&players[13]);
			assert (players[13].hasCondition(PlayerChar::SEE_INVISIBLE), "Potion of See Invisible");

			comment("Finished Potion tests.");
		}
};
