/**
 * @file helpscreen.h
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member declarations for the HelpScreen class
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

/** Interface state that shows the various game controls
  *
  * Environment variables: input device (e.g., keyboard) and output device (e.g., monitor)
  */
class HelpScreen : public UIState {
	public:
		/** Constructor. */
		HelpScreen(PlayerChar*, Level*);
		/** Render the controls. */
		virtual void draw(TCODConsole*);
		/** Handle the player input (just quitting). */
		virtual UIState* handleInput(TCOD_key_t);
	private:
		/** Reference to the player for when they start playing again. */
		PlayerChar* player;
		/** Reference to the level for when the game resumes. */
		Level* level;
		/** List of all hotkeys in the game. */
		static const char hotkeys[];
		/** Describes the commands that correspond to the hotkeys. */
		static const std::string descs[];
};
