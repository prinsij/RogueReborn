/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: playstate.cpp
 */ 

#include <algorithm>
#include <iostream>
#include <string>

#include "include/feature.h"
#include "include/globals.h"
#include "include/goldpile.h"
#include "include/helpscreen.h"
#include "include/invscreen.h"
#include "include/item.h"
#include "include/level.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/ripscreen.h"
#include "include/stairs.h"
#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"

/* The game can prompt the user for response.
 * This is blocking, but the level view remains.
 * Acts as a sub-uistate internal to playstate,
 * so we don't have to duplicate rendering stuff.
 */
class Prompt {
	public:
		Prompt(PlayerChar* player, Level* level)
			: player(player)
			, level(level)
		{}
		virtual ~Prompt() {};
		/* Q: Why do prompts need arbitrary rendering capabilities
		 * instead of just drawing a string?
		 * A: Sometimes the prompt needs to highlight letters to
		 * indicate the keyboard shortcuts
		 */
		virtual void showText(TCODConsole* con, int x, int y) {};
		// Transitions indicate where the owning PlayState
		// should transfer control next (could be prompt or uistate)
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

/* Player can press shift+q to enter a game-quit
 * prompt, which will ask for confirmation, then
 * transition to RIP/score screen.
 */
class QuitPrompt : public Prompt {
	public:
		QuitPrompt(PlayerChar* player, Level* level)
			: Prompt(player, level)
		{}

		virtual Transition handleInput(TCOD_key_t key) {
			if (key.c == 'y' || key.c == 'Y') {
				return Transition(NULL, new RIPScreen(player, level, "retired"));
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
{
	play->appendLog("Hello " + play->getName() + ". Welcome to the Dungeons of Doom. Type [?] for help.");
	currRoom = updateMap();
}

Room* PlayState::updateMap() {
	for (auto x=-1; x < 2; x++) {
		for (auto y=-1; y < 2; y++) {
			(*level)[player->getLocation()+Coord(x,y)].setIsSeen(Terrain::Seen);
		}
	}
	for (auto& room : level->getRooms()) {
		if (room.contains(player->getLocation(), 1)) {
			for (auto x=room.getPosition1()[0]-1; x < room.getPosition2()[0]+2; x++) {
				for (auto y=room.getPosition1()[1]-1; y < room.getPosition2()[1]+2; y++) {
					(*level)[Coord(x,y)].setIsSeen(Terrain::Seen);
				}
			}
			// rooms can't overlap
			return &room;
		}
	}
	return NULL;
}

void PlayState::draw(TCODConsole* con) {
	// Draw terrain
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			Terrain& ter = (*level)[mapPos];
			if (ter.isSeen() == Terrain::Seen) {
				auto scrPos = mapPos.asScreen();
				con->putChar(scrPos[0], scrPos[1], (*level)[mapPos].getSymbol());
				for (Feature* feat : level->getFeatures()) {
					if (feat->getLocation() == mapPos) {
						con->putChar(scrPos[0], scrPos[1], feat->getSymbol());
					}
				}
				int sightRadius = player->getSightRadius();
				if (currRoom == NULL || currRoom->getDark() == Room::DARK) {
					sightRadius = 1;
				}
				// Previously but not currently seen
				if (mapPos.distanceTo(player->getLocation()) > sightRadius &&
					(currRoom == NULL || !currRoom->contains(mapPos, 1))) {
					con->setCharForeground(scrPos[0], scrPos[1], TCODColor::grey);
				// Currently in view
				} else {
					for (Mob* mob : level->getMobs()) {
						if (mob->getLocation() == mapPos) {
							con->putChar(scrPos[0], scrPos[1], mob->getSymbol());
						}
					}
				}
			}
		}
	}

	// Display the prompt
	if (prompt != NULL) {
		prompt->showText(con, 0, 1);
	} else if (player->getLog().size() > 0) {
		con->print(0, 0, player->getLog().back().c_str());
	}
	// Display the info bar
	const int y = Coord(0, level->getSize()[1]).asScreen()[1]+1;
	con->print(0, y, (
	"Level:"+std::to_string(player->getLevel())+
	"  Hits:"+std::to_string(player->getHP())+"("+std::to_string(player->getMaxHP())+")"+
	"  Str:"+std::to_string(player->getStrength())+"("+std::to_string(player->getMaxStrength())+")"+
	"  Gold:"+std::to_string(player->getGold())+
	"  Armor:"+std::to_string(player->getArmor())).c_str());
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
	// Perform AI turns until it's the player's go
	while (true) {
		auto nextUp = level->popTurnClock();
		if (nextUp == player) {
			level->pushMob(player, 0);
			break;
		}
		//std::cout << "taking turn: " << nextUp->getName() << "\n";
		// Do AI turn
		level->pushMob(nextUp, nextUp->turn(level));
	}
	// Quitting
	if (key.c == 'Q') {
		prompt = new QuitPrompt(player, level);
		return this;
	}
	if (key.c == 'i') {
		return new InvScreen(player, level);
	}
	if (key.c == '?') {
		return new HelpScreen(player, level);
	}
	// Rest action
	if (key.c == '.') {
		level->pushMob(player, TURN_TIME);
		player->appendLog("You rest briefly");
		return this;
	}
	if (key.c == '<' || key.c == '>') {
		for (Feature* feat : level->getFeatures()) {
			Stairs* stair = dynamic_cast<Stairs*>(feat);
			if (stair != NULL) {
				if ((key.c == '>') == stair->getDirection()) {
					int currDepth = level->getDepth();
					delete level;
					level = new Level(currDepth+1);
					level->registerMob(player);
					level->generate(*player);
					currRoom = updateMap();
					return this;
				}
			}
		}
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
	if (newPos != player->getLocation() && level->contains(newPos)) {
		Mob* mob = level->monsterAt(newPos);
		if (mob != NULL) {
			std::cout << mob->getHP();
			player->appendLog("attacked " + mob->getName());
			if (mob->setCurrentHP(mob->getHP()-player->calculateDamage())) {
				level->removeMob(mob);
				player->appendLog(mob->getName() + " died, horribly");
				delete mob;
			}
			level->pushMob(player, TURN_TIME);
		} else if ((*level)[newPos].isPassable()) {
			player->setLocation(newPos);
			level->pushMob(player, TURN_TIME);
			//std::cout << "taking turn: " << player->getName() << "\n";
			currRoom = updateMap();
			bool search;
			do {
				search = false;
				for (Feature* feat : level->getFeatures()) {
					if (feat->getLocation() != newPos) {
						continue;
					}
					Item* i = dynamic_cast<Item*>(feat);
					if (i != NULL) {
						player->pickupItem(i);
						level->removeFeature(feat);
						search = true;
					}
					GoldPile* gp = dynamic_cast<GoldPile*>(feat);
					if (gp != NULL) {
						player->collectGold(gp);
						level->removeFeature(feat);
						delete feat;
						search = true;
						break;
					}
				}
			} while (search);
		}
	}
	return this;
}

PlayState::~PlayState() {
	if (prompt != NULL) {
		delete prompt;
	}
}