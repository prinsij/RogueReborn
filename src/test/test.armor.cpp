
#ifndef ARMOR_TEST
#define ARMOR_TEST

#include <string>
#include <vector>
#include <iostream>

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

			return true;
		}
};

#endif