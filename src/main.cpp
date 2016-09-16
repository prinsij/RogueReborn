#include <iostream>
#include "tcodsrc/libtcod.hpp"
#include <random>
#include <vector>

int main() {

    std::cout << "RogueReborn" << std::endl;

    //Some stdlib blabber
    std::random_device rand_device;
    std::mt19937 twister(rand_device());
    std::discrete_distribution<> distribution({3, 1});

    //Set map
    int mapx = 40, mapy = 40;
    std::vector<std::vector<int> > map;
    for (auto x=0; x < mapx; x++) {
        map.push_back(std::vector<int>());
        for (auto y=0; y < mapy; y++) {
            map[x].push_back(distribution(twister));
        }
    }

    //Init console
    TCODConsole::initRoot(mapx, mapy, "Rogue Reborn", false);

    //Player X and Y
    int px = 5, py = 5;

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
        for (auto x=0; x < mapx; x++) {
            for (auto y=0; y < mapy; y++) {
                if (map[x][y] == 0) {
                    TCODConsole::root->putChar(x, y, ' ');
                } else {
                    TCODConsole::root->putChar(x, y, '#');
                }
            }
        }

        //Place player
        TCODConsole::root->putChar(px, py,'@');

        //???
        TCODConsole::flush();
    }

    if (TCODColor::red != TCODColor::blue) {
        std::cout << "ne\n";
    } else {
        std::cout << "e\n";
    }
    return 0;
}
