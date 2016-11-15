/**
 * @file test.level.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../include/playerchar.h"
#include "../include/level.h"
#include "test.testable.cpp"

class LevelTest : public Testable {
	public:
		LevelTest(){
			std::cout << "# Creating level test" << std::endl;
		}

		bool test(){
			std::cout << "# Testing level!" << std::endl;

			Coord pos  = Coord(0,0);

			PlayerChar player = PlayerChar(pos, "test");

			Level l = Level(1, &player);

			return true;
		}
};