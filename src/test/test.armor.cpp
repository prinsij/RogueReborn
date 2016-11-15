/**
 * @file test.armor.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../include/armor.h"
#include "test.testable.cpp"

class ArmorTest : public Testable {
	public:
		ArmorTest(){}

		void test(){
			
			comment("Testing armor!");

			assert(true, "");
			assert(true, "");
			assert(true, "");

			assert(true, "");
			assert(true, "");
			assert(true, "");
		}
};