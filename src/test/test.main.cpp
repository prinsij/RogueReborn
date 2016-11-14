/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "test.armor.cpp"
#include "test.testable.cpp"

int main(){

	ArmorTest a = ArmorTest();

	a.test();

	return 0;
}