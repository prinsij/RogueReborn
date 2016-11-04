/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: playstate.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "uistate.h"

class Prompt;

class PlayState : public UIState {
	public:
		PlayState(PlayerChar*, Level*);
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
		virtual ~PlayState();
	private:
		PlayerChar* player;
		Level* level;
		Prompt* prompt;
		Room* updateMap();
		Room* currRoom;
};