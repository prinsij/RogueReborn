/**
 * @file test.tunnel.cpp
 * @author Team Rogue++
 * @date November 29, 2016
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

		void test(){

			comment("Commencing Tunnel tests");

			PlayerChar* player = new PlayerChar(Coord(0,0), "TestMan");
			Level* level = new Level(1, player);

			Room* left = new Room(Coord(1,1), Coord(5,5));
			Coord leftCenter = Coord(3,3);

			Room* right = new Room(Coord(11,1), Coord(15,5));
			Coord rightCenter = Coord(13,3);


			Tunnel tunnel = Tunnel(left, right);
			tunnel.dig(*level);

			assert(level->bfsPerp(leftCenter, rightCenter).size() > 0, "Tunnel digging works");

			delete level;
			delete player;
			delete left;
			delete right;

			comment("Finished Tunnel tests");

		}
};
