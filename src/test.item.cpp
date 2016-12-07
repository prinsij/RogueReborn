/**
 * @file test.item.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the ItemTest class
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/item.h"
#include "test.testable.h"

class ItemTest : public Testable {
	public:
		ItemTest(){}

		void test(){
			comment("Commencing Item tests...");

			Item item = Item('~', Coord(0,0), Item::FLOOR, "className", "name", "pseudoName", 0, true, true, 1);
			assert(true, "Created Item (1)");
			Item itemCon = Item('~', Coord(0,0), Item::FLOOR, "className", "name", 0, true, true, 1);
			assert(true, "Created Item (2)");

			std::vector<std::string> stringVector = {"A", "B", "C", "D"};
			stringVector = Item::shuffleNameVector(stringVector);
			assert(stringVector.size() == 4, "Shuffle Name Vector Check");

			assert(!item.isCursed(), "Item Cursed Check 1");
			item.applyEffect(Item::CURSED);
			assert(item.isCursed(), "Item Cursed Check 2");
			item.removeEffect(Item::CURSED);
			assert(!item.isCursed(), "Item Cursed Check 3");

			assert(!item.isIdentified(), "Item Identify Check 1");
			item.setIdentified(true);
			assert(item.isIdentified(), "Item Identify Check 2");

			item.setIdentified(false);
			assert(item.getDisplayName() == "pseudoName", "Item Display Name Check 1");
			item.setIdentified(true);
			assert(item.getDisplayName() == "name", "Item Display Name Check 2");

			comment("Finished Item tests.");
		}
};
