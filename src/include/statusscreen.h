/**
 * @file statusscreen.h
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member declarations for the StatusScreen class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

/** Screen which shows detailed player statistics. */

class StatusScreen : public UIState {
	public:
		/** Constructor. */
		StatusScreen(PlayerChar*, Level*);
		/** Render the controls. */
		virtual void draw(TCODConsole*);
		/** Handle the player input (just quitting). */
		virtual UIState* handleInput(TCOD_key_t);
	private:
		/** Reference to the player for when they start playing again. */
		PlayerChar* player;
		/** Reference to the level for when the game resumes. */
		Level* level;
};
