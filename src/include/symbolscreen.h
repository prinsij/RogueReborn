/**
 * @file symbolscreen.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the SymbolScreen class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

class SymbolScreen : public UIState {
	public:
		/** Constructor. */
		SymbolScreen(PlayerChar*, Level*);
		/** Render the various symbols and explanations. */
		virtual void draw(TCODConsole*);
		/** Handle the player input (just quitting). */
		virtual UIState* handleInput(TCOD_key_t);
	private:
		/** Reference to the player for when they start playing again. */
		PlayerChar* player;
		/** Reference to the level for when the game resumes. */
		Level* level;
		const static std::string symbols[];
		const static std::string explanations[];
};
