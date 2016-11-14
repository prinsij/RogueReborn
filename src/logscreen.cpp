/**
 * @file logscreen.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the LogScreen class
 */ 

#include "include/logscreen.h"
#include "include/playstate.h"
#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"

LogScreen::LogScreen(PlayerChar* player, Level* level)
	: UIState()
	, player(player)
	, level(level)
{}

UIState* LogScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		return new PlayState(player, level);
	}
	return this;
}

void LogScreen::draw(TCODConsole* con) {
	auto log = player->getLog();
	int y = 0;
	for (auto it=log.rbegin(); it != log.rend() && y < NUM_MESSAGES; ++it) {
		con->print(0, y, it->c_str());
		++y;
	}
}