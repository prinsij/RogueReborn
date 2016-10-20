#pragma once
#include "uistate.h"
#include "playerchar.h"
#include "../libtcod/include/libtcod.hpp"
#include "playstate.h"
#include "level.h"

class InvScreen : public UIState {
	public:
		InvScreen(PlayerChar*, Level*);
		void draw(TCODConsole*);
		UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		Level* level;
};
