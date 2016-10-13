#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"
#include <iostream>
#include "include/level.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/mainmenu.h"

MainMenu::MainMenu()
	: nameBuffer("")
{}

void MainMenu::draw(TCODConsole* con) {
	con->print(0, 0, "welcome to Rogue Reborn!");
	con->print(0, 1, ("Rogue's Name? " + nameBuffer).c_str());
}

UIState* MainMenu::handleInput(TCOD_key_t key) {
	if (!key.pressed) return this;
	if (key.vk == TCODK_BACKSPACE) {
		if (!nameBuffer.empty()) {
			nameBuffer.resize(nameBuffer.size()-1);
		}
	} else if (key.vk == TCODK_ENTER) {
		Level* level = new Level(0);
		PlayerChar* player = new PlayerChar(nameBuffer, Coord(10, 10));
		level->generate(*player);
		return new PlayState(player, level);
	} else if (key.c) {
		if (VALID_NAME.find(key.c) != std::string::npos) {
			nameBuffer = nameBuffer + key.c;
		}
	}
	return this;
}
