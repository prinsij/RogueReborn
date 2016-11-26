#pragma once

#include "uistate.h"
#include <string>
#include "../libtcod/include/libtcod.hpp"

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
