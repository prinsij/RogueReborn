/**
 * @file savescreen.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the SaveScreen class
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

class SaveScreen : public UIState {
	public:
		SaveScreen(PlayerChar*, Level*);
		void draw(TCODConsole* con);
		UIState* handleInput(TCOD_key_t);
		virtual ~SaveScreen();
	protected:
		PlayerChar* player;
		Level* level;
		std::string nameBuffer;
		static const std::string PROMPT;
		static const std::string KEY_HINT;
};
