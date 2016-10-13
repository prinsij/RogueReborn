#include "include/playstate.h"
#include "include/uistate.h"
#include "include/playerchar.h"
#include "include/level.h"
#include "libtcod/include/libtcod.hpp"

PlayState::PlayState(PlayerChar* play, Level* lvl)
	: player(play)
	, level(lvl)
{}

void PlayState::draw(TCODConsole* con) {
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			auto scrPos = mapPos.asScreen();
			con->putChar(scrPos[0], scrPos[1], (*level)[mapPos].getChar());
		}
	}
	for (Mob* mob : level->getMobs()) {
		auto scrPos = mob->getCoord().asScreen();
		con->putChar(scrPos[0], scrPos[1], mob->getChar());
	}
}

UIState* PlayState::handleInput(TCOD_key_t key) {
	return this;
}
