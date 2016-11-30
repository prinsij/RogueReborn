/**
 * @file mastercontroller.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member definitions for the MasterController class
 */ 

#include <iostream>
#include <string>

#include "include/coord.h"
#include "include/globals.h"
#include "include/level.h"
#include "include/mainmenu.h"
#include "include/mastercontroller.h"
#include "libtcod/include/libtcod.hpp"

MasterController::MasterController()
	: currState(new MainMenu())
{}

void MasterController::run() {
    std::cout << "Welcome to Rogue Reborn!" << std::endl;
    TCODConsole::setCustomFont("assets/terminal-large.png");
    //Init console
    TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Rogue Reborn", false);
	// floatCon is our 'false root' so we don't have to work with the root
	// console -> more flexibility and maintainability
    TCODConsole* floatCon = new TCODConsole(SCREEN_WIDTH, SCREEN_HEIGHT);
	// Limits number of flushes/second so we don't consum 100% cpu
	TCODSystem::setFps(FPS_LIMIT);
	//Game loop
    TCOD_key_t key;
	while (!TCODConsole::isWindowClosed()) {
		// control-C overrides all
		if ((key.rctrl || key.lctrl) && (key.c == 'c' || key.c == 'C')) {
			break;
		}
		auto temp = currState;
		currState = currState->handleInput(key);
		// Transition to the next state, cleaning up behind
		// us if necessary.
		if (temp != currState) {
			delete temp;
		}
		// Terminate the game on NULL return
		if (currState == NULL) {
			break;
		}
		if (key.c == FULLSCREEN_TOGGLE) {
			TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
		}
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
		floatCon->clear();
		currState->draw(floatCon);
		TCODConsole::blit(floatCon,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,TCODConsole::root,0,0);
		TCODConsole::flush();
	}
	delete floatCon;
}
