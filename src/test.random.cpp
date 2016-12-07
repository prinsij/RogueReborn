/**
 * @file test.random.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/random.h"
#include "test.testable.h"

class RandomTest : public Testable {
	public:
		RandomTest(){}

		void test(){
			comment("Commencing Random tests...");

			int randInt = -1;
			double randFP = -1.0;
			bool condition = false;


			assert(Generator::intFromRange(0,0) == 0, "Int From Range Test 1");
			assert(Generator::intFromRange(5,5) == 5, "Int From Range Test 2");

			condition = true;
			for (int i = 0 ; i < 40 && condition ; i ++) {
				randInt = Generator::intFromRange(0, 60);
				condition &= randInt >= 0 && randInt <= 60;
			}
			assert(condition, "Int From Range Test 3");


			condition = true;
			for (int i = 0 ; i < 40 && condition; i ++) {
				randFP = Generator::rand();
				condition &= randFP >= 0 && randFP < 1;
			}
			assert(condition, "Random Float Test");


			condition = Generator::rand();
			bool notCondition = !condition;
			for (int i = 0 ; i < 10 && (condition != notCondition); i ++) {
				condition = Generator::randBool();
			}
			assert(condition == notCondition, "Random Bool Test");

			condition = true;
			for (int i = 0 ; i < 40 && condition; i ++) {
				randInt = Generator::randPercent();
				condition &= randInt >= 0 && randInt <= 100;
			}
			assert(condition, "Random Percent Test");


			condition = true;
			for (int i = 0 ; i < 10 && condition; i ++) {
				Coord a = Coord(Generator::intFromRange(0, 100), Generator::intFromRange(0, 100));
				Coord b = Coord(Generator::intFromRange(0, 100), Generator::intFromRange(0, 100));

				Coord r = Generator::randPosition(a, b);

				int minX = std::min(a[0], b[0]);
				int maxX = std::max(a[0], b[0]);
				int minY = std::min(a[1], b[1]);
				int maxY = std::max(a[1], b[1]);

				condition &= r[0] >= minX && r[0] <= maxX && r[1] >= minY && r[1] <= maxY;
			}
			assert(condition, "Random Position Test");

			assert(Generator::nDx(1, 1) == 1, "nDx Test 1");
			assert(Generator::nDx(2, 1) == 2, "nDx Test 2");
			assert(Generator::nDx(1, 2) >= 1 && Generator::nDx(1, 2) <= 2, "nDx Test 3");
			assert(Generator::nDx(3, 4) >= 3 && Generator::nDx(3, 4) <= 12, "nDx Test 4");

			comment("Finished Random tests.");
		}
};
