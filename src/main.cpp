#include <iostream>
#include "libtcod/include/libtcod.hpp"
#include "include/mastercontroller.h"
#include "include/level.h"
#include "include/playerchar.h"
#include <vector>
#include <string>

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
