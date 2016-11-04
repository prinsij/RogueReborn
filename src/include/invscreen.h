/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: invscreen.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "playstate.h"
#include "uistate.h"

class InvScreen : public UIState {
	public:
		InvScreen(PlayerChar*, Level*);
		void draw(TCODConsole*);
		UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		Level* level;
};