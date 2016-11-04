/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: invscreen.cpp
 */ 

#include "include/invscreen.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "libtcod/include/libtcod.hpp"

InvScreen::InvScreen(PlayerChar* player, Level* level)
	: player(player)
	, level(level)
{}

UIState* InvScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		return new PlayState(player, level);
	}
	return this;
}

void InvScreen::draw(TCODConsole* con) {
	int y = 0;
	for (auto& pair : player->getInventory().getContents()) {
		con->print(0, y,
			(std::string(1, pair.first)+") "+std::to_string(pair.second.quantity)+" "
			+pair.second.item->getDisplayName()).c_str());
		++y;
	}
}