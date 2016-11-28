/**
 * @file test.food.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/food.h"
#include "include/playerchar.h"
#include "test.testable.h"

class FoodTest : public Testable {
	public:
		FoodTest(){}

		void test(){
			comment("Commencing Food tests...");

			Food foodCon = Food(Coord(0,0), Item::FLOOR);
			assert(true, "Created Food");

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
