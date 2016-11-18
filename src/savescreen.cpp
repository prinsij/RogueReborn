#include "include/savescreen.h"
#include "include/playerchar.h"
#include "include/level.h"
#include "include/playstate.h"
#include "include/globals.h"
#include <string>
#include <fstream>
#include <iostream>
#include "include/saving.h"

SaveScreen::SaveScreen(PlayerChar* player, Level* level)
	: player(player)
	, level(level)
	, nameBuffer("")
{}

void SaveScreen::draw(TCODConsole* con) {
	con->print(1, 1, (nameBuffer+"$").c_str());
}

UIState* SaveScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		return new PlayState(player, level);
	}
	if (key.vk == TCODK_ENTER && nameBuffer.size() > 0) {
		//write out
		std::ofstream savefile;
		savefile.open(nameBuffer, std::ios::out);
		if (savefile.is_open()) {
			savefile << encode(player, level);
			savefile.close();
			return NULL;
		} else {
			std::cout << "FAILED TO OPEN SAVEFILE\n";
		}
	} else if (key.c) {
		if (VALID_NAME.find(key.c) != std::string::npos && nameBuffer.size() < NAME_LENGTH) {
			nameBuffer = nameBuffer + key.c;
		}
	}
	if (key.vk == TCODK_BACKSPACE && nameBuffer.size() > 0) {
		nameBuffer.resize(nameBuffer.size()-1); 
	}
	return this;
}
