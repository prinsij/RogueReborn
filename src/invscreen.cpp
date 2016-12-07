/**
 * @file invscreen.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the InvScreen class
 */ 

#include <functional>

#include "include/invscreen.h"
#include "include/itemzone.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "libtcod/include/libtcod.hpp"

InvScreen::InvScreen(PlayerChar* player, Level* level,
		filtFunc filter, transFunc trans, bool escapeable, std::string prompt)
	: player(player)
	, level(level)
	, filter(filter)
	, transition(trans)
	, escapeable(escapeable)
	, prompt(prompt)
{}

UIState* InvScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE && this->escapeable) {
		return new PlayState(player, level);
	}
	auto items = player->getInventory().getItem(key.c);
	if (items != NULL && filter(items->front())) {
		return transition(items->front(), player, level);
	}
	return this;
}

void InvScreen::draw(TCODConsole* con) {
	int y = 0;
	for (auto& pair : player->getInventory().getContents()) {
		if (not filter(pair.second.front())) continue;
		std::string prefix = pair.second.size() > 1
			? std::to_string(pair.second.size())
			: "A";
		con->print(0, y,
			(std::string(1, pair.first)+") "+ prefix + " "
			+pair.second.front()->getDisplayName()).c_str());
		++y;
	}
	if (prompt == "") {
		con->print(1, y+1, ("Weight: " + std::to_string(player->getInventory().getCurrWeight()) + "/" +
										 std::to_string(player->getInventory().getMaxWeight()) +
							" pounds"
							).c_str());
	} else {
		con->print(1, y+1, prompt.c_str());
	}
}
