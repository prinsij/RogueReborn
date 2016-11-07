/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: mainmenu.h
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "globals.h"
#include "uistate.h"

class MainMenu : public UIState {
	public:
		MainMenu();
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		std::string nameBuffer;
};