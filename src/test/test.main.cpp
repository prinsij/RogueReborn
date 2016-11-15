/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.armor.cpp"
#include "test.level.cpp"
#include "test.testable.cpp"

int main(){

	ArmorTest a = ArmorTest();
	a.test();


	LevelTest l = LevelTest();
	l.test();

	return 0;
}