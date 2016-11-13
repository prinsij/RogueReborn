/**
 * @file invscreen.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the InvScreen class
 */ 

#include "include/invscreen.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "libtcod/include/libtcod.hpp"
#include "include/itemzone.h"
#include <functional>

InvScreen::InvScreen(PlayerChar* player, Level* level, 
		filtFunc filter, transFunc trans, bool escapeable)
	: player(player)
	, level(level)
	, filter(filter)
	, transition(trans)
	, escapeable(escapeable)
{}

UIState* InvScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE && this->escapeable) {
		return new PlayState(player, level);
	}
	ItemZone::KeysItem* item = player->getInventory().getItem(key.c);
	if (item != NULL && filter(item->item)) {
		return transition(item->item, player, level);
	}
	return this;
}

void InvScreen::draw(TCODConsole* con) {
	int y = 0;
	for (auto& pair : player->getInventory().getContents()) {
		if (not filter(pair.second.item)) continue;
		con->print(0, y,
			(std::string(1, pair.first)+") "+std::to_string(pair.second.quantity)+" "
			+pair.second.item->getDisplayName()).c_str());
		++y;
	}
}
