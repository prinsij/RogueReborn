#pragma once
#include "../libtcod/include/libtcod.hpp"

class UIState {
	public:
		UIState();
		// Render the current UI
		virtual void draw(TCODConsole*);
		// Do whatever is needed in response to keypresses
		// then return state to transition to (can be self)
		virtual UIState* handleInput(TCOD_key_t);
		virtual ~UIState();
};
