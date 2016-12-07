/**
 * @file test.coord.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the CoordTest class
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/coord.h"
#include "test.testable.h"

/**
 * @brief      Tests the Coord class.
 */
class CoordTest : public Testable {
	public:
		CoordTest(){}

		void test(){

			comment("Testing coord!");

			assert(Coord(0,0) < Coord(1,1), "Coordinate comparison (Greater than)");
			assert(Coord(0,0) == Coord(0,0), "Coordinate comparison (Equality)");
			assert(!(Coord(0,0) == Coord(1,1)), "Coordinate comparison fail (Equality)");

			assert((Coord(2,3)+Coord(1,2)) == Coord(3,5), "Coordinate addition");
			assert((Coord(2,3)-Coord(1,2)) == Coord(1,1), "Coordinate subtraction");
		}
};
