/**
 * @file food.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Member definitions for the Food class
 */ 

#include "include/coord.h"
#include "include/food.h"
#include "include/item.h"
#include "include/random.h"

Food::Food(Coord location, Item::Context context)
	: Item(':', location, context, "Food", "Some Rations of Food", 0, true, false, FOOD_WEIGHT) {}

bool Food::activate(PlayerChar* player) {
	int foodLife = player->getFoodLife()/3;

	if (Generator::rand() < 0.60) {
		player->appendLog("Yum, that tasted good");
		foodLife += Generator::intFromRange(FOOD_MIDDLE, FOOD_HIGH);
	} else {
		player->appendLog("Yuk, that food tasted awful");
		foodLife += Generator::intFromRange(FOOD_LOW, FOOD_MIDDLE);
	}

	player->setFoodLife(foodLife);

	return true;
}
