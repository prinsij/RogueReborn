/**
 * @file test.goldpile.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/goldpile.h"
#include "test.testable.h"

class GoldPileTest : public Testable {
	public:
		GoldPileTest(){}

		void test(){
			comment("Commencing GoldPile tests...");

			GoldPile goldpile = GoldPile(Coord(0,0), 5);
			assert(true, "Created GoldPile");
			assert(goldpile.getQuantity() == 5, "GoldPile Quantity Check");

			comment("Finished GoldPile tests.");
		}
};
