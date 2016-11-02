#pragma once
#include "uistate.h"
#include "../libtcod/include/libtcod.hpp"

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
