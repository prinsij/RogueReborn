#include "include/mainmenu.h"
#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"
#include <iostream>

MainMenu::MainMenu() {}

void MainMenu::draw(TCODConsole* con) {
	con->print(0, 0, "welcome to Rogue Reborn!");
	con->print(0, 1, ("Rogue's Name? " + nameBuffer).c_str());
}

UIState* MainMenu::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_BACKSPACE) {
		if (!nameBuffer.empty()) {
			nameBuffer.resize(nameBuffer.size()-1);
		}
	} else if (key.vk == TCODK_ENTER) {
		return new UIState();
	} else if (key.c) {
		nameBuffer = nameBuffer + key.c;
	}
	return this;
}
