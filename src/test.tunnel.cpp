/**
 * @file test.tunnel.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/tunnel.h"
#include "test.testable.h"

class TunnelTest : public Testable {
	public:
		TunnelTest(){}

		const int NUM_OF_TESTS = 5;

		void test(){

			comment("Commencing Tunnel tests");

			PlayerChar* player = new PlayerChar(Coord(0,0), "TestMan");

			Coord t = Generator::randPosition(Coord(0,0), Coord(10,10));
			Room* a = new Room(t, t+Generator::randPosition(Coord(2,2), Coord(5,5)));
			t = Generator::randPosition(Coord(10,10), Coord(20,20));
			Room* b = new Room(Coord(11,1), Coord(15,5));

			Tunnel tunnel = Tunnel(a, b);

			Level* level;

			for (auto i = 0; i < NUM_OF_TESTS; i++){

				level = new Level(i+1, player);
				tunnel.dig(*level);

				assert(level->bfsPerp(a->getPosition1(), b->getPosition2()).size() > 0, "Tunnel digging works");

				delete level;
			}

			delete player;
			delete a;
			delete b;

			comment("Finished Tunnel tests");

		}
};
