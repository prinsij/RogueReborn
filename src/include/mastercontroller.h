/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: mastercontroller.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

/** Controls the top level flow flow of the
 *  application and main game loop.
 *  Called directly from main.
 */
class MasterController {
	public:
		/** All game logic is inside, so no params
		 *  needed for constructor
		 */
		MasterController();
		/** Main game loop */
		void run();
	private:
		/** Current interface state */
		UIState* currState;
		/** Max number of frames per second */
		const int FPS_LIMIT = 20;
};
