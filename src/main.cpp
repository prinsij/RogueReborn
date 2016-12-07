/**
 * @file main.cpp
 * @author Team Rogue++
 * @date December 02, 2016
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

void putString(int x, int y, std::string text) {
	for (uint i = 0; i < text.size(); i++){
		TCODConsole::root->putChar(x+i,y,text[i]);
	}
}

/**
  * Execution starts here
  */
int main(int argv, char** args) {
	MasterController controller;
	controller.run();
}
