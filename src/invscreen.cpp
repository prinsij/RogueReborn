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
	for (auto item : player->getInventory()) {
		con->print(0, y, item.first->getName().c_str());
	}
}
