#include <iostream>
#include "libtcod/include/libtcod.hpp"
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


    // Map dimensions (from original Rogue) 
    uint mapx = 80, mapy = 25;

    std::vector<std::vector<int> > map;

	Generator rand;

    for (uint x = 0; x < mapx; x++) {
        map.push_back(std::vector<int>());
        for (uint y = 0; y < mapy; y++) {
			int block = rand() < .25 ? 1 : 0;
            map[x].push_back(block);
        }
    }

    //Init console
    TCODConsole::initRoot(mapx, mapy + 5, "Rogue Reborn", false);

    //Player X and Y
    uint px = 5, py = 5;

    //Game loop
    while (!TCODConsole::isWindowClosed()) {

    	//Handle user input
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        //Arrow controls
        if (key.vk == TCODK_UP) {
            if (py > 0 and map[px][py-1] == 0) {
                py -= 1;
            }
        } else if (key.vk == TCODK_DOWN) {
            if (py < mapy-1 and map[px][py+1] == 0) {
                py += 1;
            }
        } else if (key.vk == TCODK_LEFT) {
            if (px > 0 and map[px-1][py] == 0) {
                px -= 1;
            }
        } else if (key.vk == TCODK_RIGHT) {
            if (px < mapx-1 and map[px+1][py] == 0) {
                px += 1;
            }
        }

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
        }


        //Redraw
        TCODConsole::root->clear();
        for (uint x=0; x < mapx; x++) {
            for (uint y=0; y < mapy; y++) {
                if (map[x][y] == 0) {
                    TCODConsole::root->putChar(x, y, ' ');
                } else {
                    TCODConsole::root->putChar(x, y, '#');
                }
            }
        }


        putString(0, 26, "test");

        //Place player
        TCODConsole::root->putChar(px, py,'@');

        //Push changes to screen
        TCODConsole::flush();
    }
    return 0;
}
