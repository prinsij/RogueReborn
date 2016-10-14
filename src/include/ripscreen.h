#pragma once
#include "uistate.h"
#include "playerchar.h"
#include "../libtcod/include/libtcod.hpp"

class RIPScreen : public UIState {
	public:
		RIPScreen(PlayerChar*);
		virtual void draw(TCODConsole*);
	private:
		PlayerChar* player;
};
