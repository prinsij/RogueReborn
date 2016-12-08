/**
 * @file test.food.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the FoodTest class
 */ 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "include/food.h"
#include "include/playerchar.h"
#include "test.testable.h"

/**
 * @brief      Tests the Food class.
 */
class FoodTest : public Testable {
	public:
		FoodTest(){}

		void test(){
			comment("Commencing Food tests...");

			try {
				Food foodCon = Food(Coord(0,0), Item::FLOOR);
				assert(true, "Created Food");
			} catch (const std::exception& e) {
				assert(false, "Failure creating Food");
			}

			for (int i = 0 ; i < 10 ; i ++) {
				PlayerChar player = PlayerChar(Coord(0,0), "Player " + std::to_string(i));

				Food food = Food(Coord(0,0), Item::FLOOR);

				int foodLife = player.getFoodLife();
				food.activate(&player);

				int deltaHP = player.getFoodLife() - foodLife/3;
				assert(deltaHP >= Food::FOOD_LOW && deltaHP <= Food::FOOD_HIGH, "Food increase bounds");
			}

			comment("Finished Food tests.");
		}
};
