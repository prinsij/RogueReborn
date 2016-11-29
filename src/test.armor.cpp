/**
 * @file test.armor.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "test.testable.h"

class ArmorTest : public Testable {
	public:
		ArmorTest(){}

		void test(){

			comment("Testing armor!");

			for (auto i = 0; i < 10; i++){
				Armor a = Armor(Coord(0,0));
				assert(a.getRating() >= 0, "Armor is meaningful");
			}
		}
};
