/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: mastercontroller.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class MasterController {
	public:
		MasterController();
		void run();
	private:
		UIState* currState;
		const int FPS_LIMIT = 20;
};