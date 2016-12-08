/**
 * @file test.goldpile.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the GoldPileTest class
 */ 

#include <exception>
#include <string>
#include <vector>

#include "include/goldpile.h"
#include "test.testable.h"

/**
 * @brief      Tests the GoldPile class.
 */
class GoldPileTest : public Testable {
	public:
		GoldPileTest(){}

		void test(){
			comment("Commencing GoldPile tests...");

			try {
				GoldPile goldpile = GoldPile(Coord(0,0), 5);
				assert(true, "Created GoldPile");
			} catch (const std::exception& e) {
				assert(false, "Failure creating GoldPile");
			}
			GoldPile goldpile = GoldPile(Coord(0,0), 5);
			assert(goldpile.getQuantity() == 5, "GoldPile Quantity Check");

			comment("Finished GoldPile tests.");
		}
};
