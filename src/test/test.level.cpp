/**
 * @file test.level.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "../include/playerchar.h"
#include "../include/level.h"
#include "test.testable.cpp"

class LevelTest : public Testable {
	public:
		LevelTest(){}

		void test(){

			comment("Testing level!");			

			Coord pos  = Coord(0,0);
			PlayerChar player = PlayerChar(pos, "test");
			Level l = Level(1, &player);
			Level* lp = &l;

			assert(lp != nullptr, "Level pointer not null");

			assert(true, "wow!");

		}
};