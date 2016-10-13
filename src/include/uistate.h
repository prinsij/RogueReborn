#pragma once
#include "../libtcod/include/libtcod.hpp"

class UIState {
	public:
		UIState();
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
		virtual ~UIState();
};
