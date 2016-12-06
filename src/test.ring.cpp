/**
 * @file test.ring.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/playerchar.h"
#include "include/ring.h"
#include "test.testable.h"

class RingTest : public Testable {
	public:
		RingTest(){}

		void test(){
			comment("Commencing Ring tests...");

			Ring ringCon = Ring(Coord(0,0));
			assert(true, "Created Ring (1)");
			Ring ringCon2 = Ring(Coord(0,0), Item::FLOOR, 0);
			assert(true, "Created Ring (2)");

			std::vector<Ring> rings;
			std::vector<PlayerChar> players;

			for (int i = 0 ; i < 11 ; i ++) {
				rings.push_back(Ring(Coord(0,0), Item::FLOOR, i));
				players.push_back(PlayerChar(Coord(0,0), "Player Ring " + std::to_string(i)));

				rings[i].ringValue = 0;
			}

			rings[0].activate(&players[0]);
			assert (players[0].hasCondition(PlayerChar::STEALTHY), "Ring of Stealth Activate");
			rings[0].deactivate(&players[0]);
			assert (!players[0].hasCondition(PlayerChar::STEALTHY), "Ring of Stealth Deactivate");

			rings[1].activate(&players[1]);
			assert (players[1].hasCondition(PlayerChar::RANDOM_TELEPORTATION), "Ring of Teleportation Activate");
			rings[1].deactivate(&players[1]);
			assert (!players[1].hasCondition(PlayerChar::RANDOM_TELEPORTATION), "Ring of Teleportation Deactivate");

			rings[2].activate(&players[2]);
			assert (players[2].hasCondition(PlayerChar::REGENERATION), "Ring of Regeneration Activate");
			rings[2].deactivate(&players[2]);
			assert (!players[2].hasCondition(PlayerChar::REGENERATION), "Ring of Regeneration Deactivate");

			rings[3].activate(&players[3]);
			assert (players[3].hasCondition(PlayerChar::DIGESTION), "Ring of Digestion Activate");
			rings[3].deactivate(&players[3]);
			assert (!players[3].hasCondition(PlayerChar::DIGESTION), "Ring of Digestion Deactivate");

			int strength4 = players[4].getStrength()/2;
			players[4].setStrength(strength4);
			rings[4].activate(&players[4]);
			assert (players[4].getStrength() == strength4 + rings[4].ringValue, "Ring of Add Strength Activate");
			rings[4].deactivate(&players[4]);
			assert (players[4].getStrength() == strength4, "Ring of Add Strength Deactivate");

			rings[5].activate(&players[5]);
			assert (players[5].hasCondition(PlayerChar::SUSTAIN_STRENGTH), "Ring of Sustain Strength Activate");
			rings[5].deactivate(&players[5]);
			assert (!players[5].hasCondition(PlayerChar::SUSTAIN_STRENGTH), "Ring of Sustain Strength Deactivate");

			int dexterity6 = players[6].getDexterity();
			rings[6].activate(&players[6]);
			assert (players[6].getDexterity() == dexterity6 + rings[6].ringValue, "Ring of Dexterity Activate");
			rings[6].deactivate(&players[6]);
			assert (players[6].getDexterity() == dexterity6, "Ring of Dexterity Deactivate");

			rings[7].activate(&players[7]);
			assert (true, "Potion of Adornment Activate");
			rings[7].deactivate(&players[7]);
			assert (true, "Potion of Adornment Deactivate");

			rings[8].activate(&players[8]);
			assert (players[8].hasCondition(PlayerChar::SEE_INVISIBLE), "Ring of See Invisible Activate Activate");
			rings[8].deactivate(&players[8]);
			assert (!players[8].hasCondition(PlayerChar::SEE_INVISIBLE), "Ring of See Invisible Activate Deactivate");

			rings[9].activate(&players[9]);
			assert (players[9].hasCondition(PlayerChar::MAINTAIN_ARMOR), "Ring of Maintain Armor Activate");
			rings[9].deactivate(&players[9]);
			assert (!players[9].hasCondition(PlayerChar::MAINTAIN_ARMOR), "Ring of Maintain Armor Deactivate");

			rings[10].activate(&players[10]);
			assert (players[10].hasCondition(PlayerChar::SEARCH), "Ring of Searching Activate");
			rings[10].deactivate(&players[10]);
			assert (!players[10].hasCondition(PlayerChar::SEARCH), "Ring of Searching Deactivate");

			comment("Finished Ring tests.");
		}
};
