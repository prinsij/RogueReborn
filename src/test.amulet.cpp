/**
 * @file test.amulet.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/amulet.h"
#include "test.testable.h"

class AmuletTest : public Testable {
	public:
		AmuletTest(){}

		void test(){
			comment("Commencing Amulet tests...");

			Amulet amuletCon = Amulet(Coord(0,0), Item::FLOOR);
			assert(true, "Created Amulet");
			
			comment("Finished Amulet tests.");
		}
};
