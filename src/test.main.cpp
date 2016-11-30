/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date November 14.2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.amulet.cpp"
#include "test.armor.cpp"
#include "test.coord.cpp"
#include "test.food.cpp"
#include "test.level.cpp"
#include "test.potion.cpp"
#include "test.playerchar.cpp"
#include "test.ring.cpp"
#include "test.scroll.cpp"
#include "test.wand.cpp"
#include "test.weapon.cpp"
#include "test.testable.h"

int main() {
	ArmorTest().test();
	AmuletTest().test();
	CoordTest().test();
	FoodTest().test();
	LevelTest().test();
	PlayerCharTest().test();
	PotionTest().test();
	RingTest().test();
	ScrollTest().test();
	WandTest().test();
	WeaponTest().test();

	return 0;
}
