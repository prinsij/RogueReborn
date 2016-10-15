#include "include/mastercontroller.h"
#include "include/coord.h"
#include "libtcod/include/libtcod.hpp"
#include "include/mainmenu.h"
#include <iostream>
#include <string>
#include "include/level.h"

MasterController::MasterController()
	: currState(new MainMenu())
{}

void MasterController::run() {
	const int spacer = 5;
    std::cout << "Welcome to Rogue Reborn!" << std::endl;
    TCODConsole::setCustomFont("assets/terminal.png");
    //Init console
	Coord lSize = Level::getSize();
    TCODConsole::initRoot(lSize[0], lSize[1] + spacer, "Rogue Reborn", false);
    TCODConsole* floatCon = new TCODConsole(lSize[0], lSize[1] + spacer);
	TCODSystem::setFps(FPS_LIMIT);
	//Game loop
    while (!TCODConsole::isWindowClosed()) {	
        TCOD_key_t key;
		auto temp = currState;
		currState = currState->handleInput(key);	
		if (temp != currState) {
			delete temp;
		}
		if (currState == NULL) {
			break;
		}
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		floatCon->clear();
		currState->draw(floatCon);
		TCODConsole::blit(floatCon,0,0,lSize[0],lSize[1]+spacer,TCODConsole::root,0,0);
		TCODConsole::flush();	
	}
	delete floatCon;
}
