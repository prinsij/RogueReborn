/**
 * @file test.stairs.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the StairsTest class
 */ 

#include <exception>
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

			try {
				Stairs stairs = Stairs(Coord(0,0), true);
				assert(true, "Created Stairs");
			} catch (const std::exception& e) {
				assert(false, "Failure creating Stairs");
			}
			Stairs stairs = Stairs(Coord(0,0), true);
			assert(stairs.getDirection(), "Stairs Direction Check");

			comment("Finished Stairs tests.");
		}
};
