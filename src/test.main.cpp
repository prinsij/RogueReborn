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

	std::vector<Testable*> tests;

	tests.push_back(new ArmorTest());
	tests.push_back(new AmuletTest());
	tests.push_back(new CoordTest());
	tests.push_back(new FoodTest());
	tests.push_back(new LevelTest());
	tests.push_back(new PlayerCharTest());
	tests.push_back(new PotionTest());
	tests.push_back(new RingTest());
	tests.push_back(new ScrollTest());
	tests.push_back(new WandTest());
	tests.push_back(new WeaponTest());

	for (Testable* t : tests){
		t->test();
		delete t;
	}

	return 0;
}
