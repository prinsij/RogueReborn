/**
 * @file test.level.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "test.testable.cpp"
#include "include/playerchar.h"
#include "include/level.h"
#include "include/random.h"

class LevelTest : public Testable {
	public:
		LevelTest(){}

		const int LEVEL_DEPTH = 5;
		const int RANDOM_TEST_COUNT = 5;

		void test(){

			comment("Testing level!");			

			Coord pos  = Coord(0,0);
			PlayerChar player = PlayerChar(pos, "test");


			Level l = Level(LEVEL_DEPTH, &player);
			Level* lp = &l;

			assert(lp != nullptr, "Level pointer not null");

			assert(l.getDepth() == LEVEL_DEPTH, "Level depth correct");

			l.clear();

			//BFS PERP
			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsPerp(Coord(1,1), Coord(target+1,1));

				
				assert(path.size() == uint(target+1), "BFS perp along a straight horizontal line works");
			}

			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsPerp(Coord(1,1), Coord(1,target+1));

				
				assert(path.size() == uint(target+1), "BFS perp along a straight vertical line works");
			}

			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsPerp(Coord(1,1), Coord(target+1,target+1));

				
				assert(path.size() == uint(2*target+1), "BFS perp along a diagonal line works");
			}

			//BFS DIAG
			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsDiag(Coord(1,1), Coord(target+1,1));

				
				assert(path.size() == uint(target+1), "BFS diag along a straight horizontal line works");
			}

			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsDiag(Coord(1,1), Coord(1,target+1));

				
				assert(path.size() == uint(target+1), "BFS diag along a straight vertical line works");
			}

			for (auto i = 0; i < RANDOM_TEST_COUNT; i++){

				//Path size is inclusive. Going from N to M involves M-N+1 locations.
				int target = Generator::intFromRange(5,30);
				std::vector<Coord> path = l.bfsDiag(Coord(1,1), Coord(target+1,target+1));

				
				assert(path.size() == uint(target+1), "BFS diag along a diagonal line works");
			}
		}
};