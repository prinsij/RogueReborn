#pragma once
#include "uistate.h"
#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"

class PlayState : public UIState {
	public:
		PlayState(PlayerChar*, Level*);
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		Level* level;
};
