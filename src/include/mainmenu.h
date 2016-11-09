/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: mainmenu.h
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

/** Start screen of the game.
 * Should include splash art, and
 * name prompt.
 */
class MainMenu : public UIState {
	public:
		/** Constructor. */
		MainMenu();
		/** Render the splash art, name prompt. */
		virtual void draw(TCODConsole*);
		/** Handle input (start game, edit name buffer). */
		virtual UIState* handleInput(TCOD_key_t);
	private:
		/** Candidate for character name as the player types it. */
		std::string nameBuffer;
};
