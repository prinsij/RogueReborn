/**
 * @file test.levelgen.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/level.h"
#include "test.testable.h"

class LevelGenTest : public Testable {
	public:
		LevelGenTest(){}

		const int NUMBER_OF_TIMES_TO_BFS = 1000;
		const int NUMBER_OF_LEVELS_TO_TEST = 10;

		void test(){

			comment("Commencing LevelGen tests");

			PlayerChar* player = new PlayerChar(Coord(0,0), "Test");
			Level* level;

			for (auto i = 0; i < NUMBER_OF_LEVELS_TO_TEST; i++){
				level = new Level(1, player);
				level->generate();

				bool probablyOk = true;
				for (auto j = 0; j < NUMBER_OF_TIMES_TO_BFS; j++){
					probablyOk *= level->bfsPerp(level->getRandomEmptyPosition(), level->getRandomEmptyPosition()).size() > 0;
				}
				assert(probablyOk, "Level is probably connected");

				delete level;
			}

			delete player;

			comment("Finished LevelGen tests");
		}
};
