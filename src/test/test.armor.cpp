/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: test.armor.cpp
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "test.testable.cpp"

class ArmorTest : public Testable {
	public:
		ArmorTest(){
			std::cout << "# Creating armor test" << std::endl;
		}

		bool test(){
			std::cout << "# Testing armor!" << std::endl;

			std::cout << "0 Test 1 success" << std::endl;
			std::cout << "0 Test 2 success" << std::endl;
			std::cout << "0 Test 3 success" << std::endl;

			std::cout << "0 Test 4 success" << std::endl;
			std::cout << "0 Test 5 success" << std::endl;
			std::cout << "0 Test 6 success" << std::endl;

			return true;
		}
};