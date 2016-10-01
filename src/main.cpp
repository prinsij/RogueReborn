#include <iostream>
#include "libtcod/include/libtcod.hpp"
#include "include/level.h"
#include "include/playerchar.h"
#include "include/random.h"
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
    std::cout << "Welcome to Rogue Reborn!" << std::endl;

    TCODConsole::setCustomFont("assets/terminal-large.png");

	Generator rand;

	PlayerChar player(Coord(10, 10));
	auto level = Level(0);
	level.generate(player);

    //Init console
    TCODConsole::initRoot(level.getSize()[0], level.getSize()[1] + 5, "Rogue Reborn", false);

    //Game loop
    while (!TCODConsole::isWindowClosed()) {

    	//Handle user input
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        //Arrow controls
		auto newPos = player.getCoord().copy();
        if (key.vk == TCODK_UP) {
			newPos -= Coord(0, 1);
        } else if (key.vk == TCODK_DOWN) {
			newPos += Coord(0, 1);
        } else if (key.vk == TCODK_LEFT) {
			newPos -= Coord(1, 0);
        } else if (key.vk == TCODK_RIGHT) {
            newPos += Coord(1, 0);
        }
		if (level.contains(newPos) and level[newPos].isPassable()) {
			player.setCoord(newPos);
		}

		/*
        //Keypad controls
        switch (key.vk){

			case TCODK_KP1:
	            if ((py < mapy-1 and px > 0) and map[px-1][py+1] == 0) {
	                py += 1;
	                px -= 1;
	            }
				break;

			case TCODK_KP2:
	            if (py < mapy-1 and map[px][py+1] == 0) {
	                py += 1;
	            }
				break;

			case TCODK_KP3:
	            if ((py < mapy-1 and px < mapx-1) and map[px+1][py+1] == 0) {
	                py += 1;
	                px += 1;
	            }

				break;

			case TCODK_KP4:
	            if (px > 0 and map[px-1][py] == 0) {
	                px -= 1;
	            }
				break;

			case TCODK_KP6:
	            if (px < mapx-1 and map[px+1][py] == 0) {
	                px += 1;
	            }
				break;

			case TCODK_KP7:
	            if ((py > 0 and px > 0) and map[px-1][py-1] == 0) {
	                py -= 1;
	                px -= 1;
	            }
				break;

			case TCODK_KP8:
	            if (py > 0 and map[px][py-1] == 0) {
	                py -= 1;
	            }
				break;

			case TCODK_KP9:
	            if ((py > 0 and px < mapx-1) and map[px+1][py-1] == 0) {
	                py -= 1;
	                px += 1;
	            }
				break;

			default:
				break;
        }*/


        //Redraw
        TCODConsole::root->clear();
        for (auto x=0; x < level.getSize()[0]; x++) {
            for (auto y=0; y < level.getSize()[1]; y++) {
					TCODConsole::root->putChar(x, y, level[Coord(x, y)].getChar());
            }
        }

        putString(0, 26, "test");

        //Place player
        TCODConsole::root->putChar(player[0], player[1],'@');

        //Push changes to screen
        TCODConsole::flush();
    }
    return 0;
}
