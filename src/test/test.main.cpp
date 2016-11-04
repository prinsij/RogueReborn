/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: test.main.cpp
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "test.armor.cpp"
#include "test.testable.cpp"

int main(){

	ArmorTest a = ArmorTest();

	bool b = a.test();

	return 0;

}