/**
 * @file mainmenu.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the MainMenu class
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;

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
		/**
		 * @brief	Sets up the PlayerChar
		 *
		 * @param	Pointer to the PlayerChar
		 */
		void setupPlayer(PlayerChar*);

		/** Candidate for character name as the player types it. */
		std::string nameBuffer;
};
