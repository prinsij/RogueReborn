/**
 * @file main.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/level.h"
#include "include/mastercontroller.h"
#include "include/playerchar.h"
#include "libtcod/include/libtcod.hpp"

using uint = unsigned int;

/**
  * Execution starts here
  */
int main(int argv, char** args) {
	MasterController controller;
	controller.run();
}
