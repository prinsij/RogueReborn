/**
 * @file test.amulet.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the AmuletTest class
 */ 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "include/amulet.h"
#include "test.testable.h"

/**
 * @brief      Tests the Amulet class.
 */
class AmuletTest : public Testable {
	public:
		AmuletTest(){}

		void test(){
			comment("Commencing Amulet tests...");

			try {
				auto amuletCon = new Amulet(Coord(0,0), Item::FLOOR);
				delete amuletCon;
				assert(true, "Created Amulet");
			} catch (const std::exception& e) {
				assert(false, "Failure to create amulet");
			}

			comment("Finished Amulet tests.");
		}
};
