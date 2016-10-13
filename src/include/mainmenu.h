#pragma once
#include "uistate.h"
#include "../libtcod/include/libtcod.hpp"
#include "globals.h"
#include <string>

class MainMenu : public UIState {
	public:
		MainMenu();
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		std::string nameBuffer;
};
