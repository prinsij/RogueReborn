/**
 * @file savescreen.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the SaveScreen class
 */ 

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>

#include "include/debug.h"
#include "include/globals.h"
#include "include/level.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/savescreen.h"
#include "include/saving.h"

const std::string SaveScreen::PROMPT = "Enter save file: ";
const std::string SaveScreen::KEY_HINT = "Press ESCAPE to continue";


SaveScreen::SaveScreen(PlayerChar* player, Level* level)
	: player(player)
	, level(level)
	, nameBuffer("")
{}

void SaveScreen::draw(TCODConsole* con) {
	con->print(1, 1, (PROMPT+nameBuffer).c_str());
	if (time(NULL) % 2 == 0) {
		con->print(1 + PROMPT.length() + nameBuffer.length(), 1, std::string("_").c_str());
	}
	con->print(1, 3, KEY_HINT.c_str());
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
#ifdef DEBUG
			std::cout << "FAILED TO OPEN SAVEFILE\n";
#endif
		}
	} else if (key.c) {
		if (VALID_NAME.find(key.c) != std::string::npos && nameBuffer.size() < NAME_LENGTH) {
			nameBuffer.push_back(key.c);
		}
	}
	if (key.vk == TCODK_BACKSPACE && nameBuffer.size() > 0) {
		nameBuffer.resize(nameBuffer.size()-1);
	}
	return this;
}

SaveScreen::~SaveScreen() {}
