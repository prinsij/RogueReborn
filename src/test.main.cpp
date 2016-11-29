/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.armor.cpp"
#include "test.level.cpp"
#include "test.playerchar.cpp"
#include "test.coord.cpp"
#include "test.testable.h"

int main(){

	ArmorTest a = ArmorTest();
	a.test();

	LevelTest l = LevelTest();
	l.test();

	PlayerCharTest pc = PlayerCharTest();
	pc.test();

	CoordTest ct = CoordTest();
	ct.test();

	return 0;
}
