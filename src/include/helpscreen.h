/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: helpscreen.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

class HelpScreen : public UIState {
	public:
		HelpScreen(PlayerChar*, Level*);
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		Level* level;
};