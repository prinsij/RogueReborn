/**
 * @file test.room.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/room.h"
#include "test.testable.h"

class RoomTest : public Testable {
	public:
		RoomTest(){}

		const int NUM_OF_RANDOM_TESTS = 50;

		bool lte(Coord a, Coord b){
			return a[0] <= b[0] && a[1] <= b[1];
		}

		void test(){

			comment("Commencing Room tests");

			for (auto i = 0; i < NUM_OF_RANDOM_TESTS; i++){
				Room r = Room(Generator::randPosition(Coord(0,0), Coord(10,10)), Generator::randPosition(Coord(10,10), Coord(19, 19)));
				assert(lte(Coord(1,1), r.getRoomSize()) && lte(r.getRoomSize(), Coord(20,20)), "Room size is within range");
				assert(lte(r.getPosition1(), r.getPosition2()), "Room bounds proper");
			}

			comment("Finished Room tests");

		}
};
