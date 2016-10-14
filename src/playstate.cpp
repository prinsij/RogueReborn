#include "include/playstate.h"
#include "include/uistate.h"
#include "include/playerchar.h"
#include "include/level.h"
#include "libtcod/include/libtcod.hpp"
#include <iostream>

PlayState::PlayState(PlayerChar* play, Level* lvl)
	: player(play)
	, level(lvl)
{}

void PlayState::draw(TCODConsole* con) {
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			auto scrPos = mapPos.asScreen();
			con->putChar(scrPos[0], scrPos[1], (*level)[mapPos].getSymbol());
		}
	}
	for (Mob* mob : level->getMobs()) {
		auto scrPos = mob->getLocation().asScreen();
		con->putChar(scrPos[0], scrPos[1], mob->getSymbol());
	}
}

UIState* PlayState::handleInput(TCOD_key_t key) {
	while (true) {
		auto nextUp = level->popTurnClock();
		if (nextUp == player) {
			break;
		}
		// Do AI turn
		level->pushMob(nextUp, 50);
	}
	//Arrow controls
	auto newPos = player->getLocation().copy();
	if (key.vk == TCODK_UP) {
		newPos -= Coord(0, 1);
	} else if (key.vk == TCODK_DOWN) {
		newPos += Coord(0, 1);
	} else if (key.vk == TCODK_LEFT) {
		newPos -= Coord(1, 0);
	} else if (key.vk == TCODK_RIGHT) {
		newPos += Coord(1, 0);
	}
	if (newPos != player->getLocation() && level->contains(newPos) && (*level)[newPos].isPassable()) {
		player->setLocation(newPos);
	}
	level->pushMob(player, 50);
	return this;
}
