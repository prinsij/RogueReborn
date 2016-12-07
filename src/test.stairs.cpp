/**
 * @file test.stairs.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/stairs.h"
#include "test.testable.h"

class StairsTest : public Testable {
	public:
		StairsTest(){}

		void test(){
			comment("Commencing Stairs tests...");

			Stairs stairs = Stairs(Coord(0,0), true);
			assert(true, "Created Stairs");
			assert(stairs.getDirection(), "Stairs Direction Check");

			comment("Finished Stairs tests.");
		}
};
