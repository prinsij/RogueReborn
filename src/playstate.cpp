#include "include/playstate.h"
#include "include/uistate.h"
#include "include/playerchar.h"
#include "include/level.h"
#include "include/ripscreen.h"
#include "libtcod/include/libtcod.hpp"
#include <iostream>
#include <string>

class Prompt {

	public:
		Prompt(PlayerChar* player, Level* level)
			: player(player)
			, level(level)
		{}
		virtual ~Prompt() {};
		virtual void showText(TCODConsole* con, int x, int y) {};
		struct Transition {
			Transition(Prompt* p, UIState* s)
				: nextPrompt(p)
				, nextState(s)
			{}
			Prompt* nextPrompt;
			UIState* nextState;
		};
		virtual Transition handleInput(TCOD_key_t key) = 0;
	protected:
		PlayerChar* player;
		Level* level;
};

class QuitPrompt : public Prompt {
	public:
		QuitPrompt(PlayerChar* player, Level* level)
			: Prompt(player, level)
		{}

		virtual Transition handleInput(TCOD_key_t key) {
			if (key.c == 'y' || key.c == 'Y') {
				return Transition(NULL, new RIPScreen(player));
			}
			if (key.c == 'n' || key.c == 'N') {
				return Transition(NULL, NULL);
			}
			return Transition(this, NULL);
		}

		virtual void showText(TCODConsole* con, int x, int y) {
			con->print(x, y, std::string("Do you wish to end your quest now (Yes/No) ?").c_str());
		}
};

PlayState::PlayState(PlayerChar* play, Level* lvl)
	: player(play)
	, level(lvl)
	, prompt(NULL)
{}

void PlayState::draw(TCODConsole* con) {
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			auto scrPos = mapPos.asScreen();
			con->putChar(scrPos[0], scrPos[1], (*level)[mapPos].getSymbol());
		}
	}
	if (prompt != NULL) {
		prompt->showText(con, 0, 0);
	}
	for (Mob* mob : level->getMobs()) {
		auto scrPos = mob->getLocation().asScreen();
		con->putChar(scrPos[0], scrPos[1], mob->getSymbol());
	}
}

UIState* PlayState::handleInput(TCOD_key_t key) {
	//delegate to the prompt if that's what we're doing
	if (prompt != NULL) {
		Prompt::Transition trans = prompt->handleInput(key);
		if (trans.nextPrompt != prompt) {
			delete prompt;
			prompt = trans.nextPrompt;
		}
		if (trans.nextState != NULL) {
			return trans.nextState;
		}
		return this;
	}
	while (true) {
		auto nextUp = level->popTurnClock();
		if (nextUp == player) {
			break;
		}
		// Do AI turn
		level->pushMob(nextUp, 50);
	}
	// Quitting
	if (key.c == 'Q') {
		prompt = new QuitPrompt(player, level);
		return this;
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

PlayState::~PlayState() {
	if (prompt != NULL) {
		delete prompt;
	}
}
