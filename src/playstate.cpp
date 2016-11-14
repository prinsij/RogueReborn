/**
 * @file playstate.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the PlayState class
 */ 

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>

#include "include/feature.h"
#include "include/food.h"
#include "include/potion.h"
#include "include/weapon.h"
#include "include/globals.h"
#include "include/goldpile.h"
#include "include/helpscreen.h"
#include "include/invscreen.h"
#include "include/item.h"
#include "include/level.h"
#include "include/logscreen.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/ripscreen.h"
#include "include/stairs.h"
#include "include/uistate.h"
#include "include/weapon.h"
#include "libtcod/include/libtcod.hpp"

class QuitPrompt2 : public PlayState {
	public:
		QuitPrompt2(PlayerChar* player, Level* level)
			: PlayState(player, level)
		{}
		virtual UIState* handleInput(TCOD_key_t key) {
			if (key.c == 'y' || key.c == 'Y') {
				return new RIPScreen(player, level, "retired");
			}
			if (key.c == 'n' || key.c == 'N') {
				return new PlayState(player, level);
			}
			return this;
		}
		virtual void draw(TCODConsole* con) {
			PlayState::draw(con);
			con->print(PROMPTX, PROMPTY, std::string("Do you wish to end your quest now (Yes/No) ?").c_str());
		}
};

class QuickDrop : public PlayState {
	public:
		QuickDrop(PlayerChar* player, Level* level, Item* item)
			: PlayState(player, level)
			, item(item)
		{}
		virtual UIState* handleInput(TCOD_key_t key) {
			item->setContext(Item::FLOOR);
			player->getInventory().remove(item);
			item->setLocation(player->getLocation());
			level->addFeature(item);
			return new PlayState(player, level);
		}
	private:
		Item* item;
};

class QuickThrow : public PlayState {
	public:
		QuickThrow(PlayerChar* player, Level* level, Item* item, Coord direction)
			: PlayState(player, level)
			, item(item)
			, direction(direction)
		{
			assert (direction != Coord(0,0));
		}
		virtual UIState* handleInput(TCOD_key_t key) {
			player->getInventory().remove(item);
			Coord newLoc = player->getLocation();
			while (true) {
				Coord next = newLoc+direction;
				auto mob = level->monsterAt(next);
				if (mob != NULL) {
					auto weap = dynamic_cast<Weapon*>(item);
					if (weap != NULL) {
						auto dmg = weap->getDamage();
						mob->hit(Generator::nDx(std::get<0>(dmg), std::get<1>(dmg)+std::get<2>(dmg)));
					} else {
						mob->hit(Item::BASE_THROW_DMG);
					}
					player->appendLog("The flying " + item->getDisplayName() + " strikes the " + mob->getName());
					delete item;
					break;
				} else if (!level->contains(next)) {
					delete item;
					player->appendLog("Somehow you threw that out-of-bounds. Plz tell the devs how");
					break;
				} else if ((*level)[next].isPassable() != Terrain::Passable) {
					player->appendLog("The " + item->getDisplayName() + " clatters off the wall");
					item->setLocation(newLoc);
					item->setContext(Item::FLOOR);
					level->addFeature(item);
					break;
				}
				newLoc += direction;
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
		Coord direction;
};

class QuickEat : public PlayState {
	public:
		QuickEat(PlayerChar* player, Level* level, Item* item)
			: PlayState(player, level)
			, item(item)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			auto food = dynamic_cast<Food*>(item);
			if (food != NULL) {
				player->eat(food);
				delete food;
			} else {
				assert (false && "not eating non-edible");
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
};

class QuickQuaff : public PlayState {
	public:
		QuickQuaff(PlayerChar* player, Level* level, Item* item)
			: PlayState(player, level)
			, item(item)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			auto pot = dynamic_cast<Potion*>(item);
			if (pot != NULL) {
				pot->activate(player);
				player->getInventory().remove(pot);
				delete pot;
			} else {
				assert (false && "tried to quaff non-potion");
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
};

class QuickWield : public PlayState {
	public:
		QuickWield(PlayerChar* player, Level* level, Item* item)
			: PlayState(player, level)
			, item(item)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			Weapon* weap = dynamic_cast<Weapon*>(item);
			if (weap != NULL) {
				player->getInventory().remove(weap);
				player->equipWeapon(weap);
			} else {
				assert (false && "tried to equip non-weapon");
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
};

class ThrowDirectionState : public PlayState {
	public:
		ThrowDirectionState(PlayerChar* player, Level* level)
			: PlayState(player, level)
		{}

		virtual void draw(TCODConsole* con) {
			PlayState::draw(con);
			con->print(PROMPTX, PROMPTY, std::string("Which direction?").c_str());
		}

		virtual UIState* handleInput(TCOD_key_t key) {
			auto direction = Coord(0, 0);
			if (key.vk == TCODK_LEFT) {
				direction = Coord(-1, 0);
			} else if (key.vk == TCODK_UP) {
				direction = Coord(0, -1);
			} else if (key.vk == TCODK_RIGHT) {
				direction = Coord(1, 0);
			} else if (key.vk == TCODK_DOWN) {
				direction = Coord(0, 1);
			} else if (key.vk == TCODK_ESCAPE) {
				return new PlayState(player, level);
			}
			if (direction != Coord(0, 0)) {
				return new InvScreen(player, level, [] (Item* i) {return i->isThrowable();},
													[=] (Item* i, PlayerChar* p, Level* l) {
														return new QuickThrow(p, l, i, direction);
													},
													true);

			}
			return this;
		}
};

PlayState::PlayState(PlayerChar* play, Level* lvl)
	: player(play)
	, level(lvl)
{
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
				if (currRoom == NULL 
					|| currRoom->getDark() == Room::DARK
					|| player->hasCondition(PlayerChar::BLIND)) {
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
	if (player->getLog().size() > 0) {
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
	// Perform AI turns until it's the player's go
	int numAIGone = 0;
	while (true) {
		auto nextUp = level->popTurnClock();
		if (nextUp == player) {
			level->pushMob(player, 0);
			break;
		}
		++numAIGone;
		// Do AI turn
		level->pushMob(nextUp, nextUp->turn(level));
		if (player->isDead()) {
			return new RIPScreen(player, level, "Killed by a " + nextUp->getName());
		}
	}
	if (numAIGone > 0) {
		player->update();
	}
	// Quitting
	if (key.c == 'Q') {
		return new QuitPrompt2(player, level);
	}
	// view inventory
	if (key.c == 'i') {
		return new InvScreen(player, level, [] (Item*) {return true;},
											[] (Item*, PlayerChar* p, Level* l) {
													return new PlayState(p, l);
												},
											true);
	}
	// view help
	if (key.c == '?') {
		return new HelpScreen(player, level);
	}
	// view log
	if (key.c == 'o') {
		return new LogScreen(player, level);
	}
	// Rest action
	if (key.c == '.') {
		level->pushMob(player, TURN_TIME);
		player->appendLog("You rest briefly");
		player->update();
		return this;
	}
	// drop item
	if (key.c == 'd') {
		if (player->getInventory().getSize() <= 0) {
			player->appendLog("You aren't carrying anything");
			goto no_drop;
		}
		for (auto feat : level->getFeatures()) {
			Item* item = dynamic_cast<Item*>(feat);
			if (item != NULL && item->getLocation() == player->getLocation()) {
				player->appendLog("There is something there already");
				goto no_drop;
			}
		}
		return new InvScreen(player, level, [] (Item*) {return true;},
											[] (Item* i, PlayerChar* p, Level* l) {
													return new QuickDrop(p, l, i);
												},
												false);
	}
	no_drop:;
	if (key.c == 'q') {
		bool canQuaff = false;
		for (auto pair : player->getInventory().getContents()) {
			Potion* pot = dynamic_cast<Potion*>(pair.second.front());
			if (pot != NULL) {
				canQuaff = true;
				break;
			}
		}
		if (canQuaff) {
			return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Potion*>(i)!=NULL;},
												[] (Item* i, PlayerChar* p, Level* l) {
													return new QuickQuaff(p, l, i);
												},
												true);
		} else {
			player->appendLog("You have nothing you can drink");
		}
	}
	// wield weapon
	if (key.c == 'w') {
		bool canWield = false;
		for (auto pair : player->getInventory().getContents()) {
			Weapon* weap = dynamic_cast<Weapon*>(pair.second.front());
			if (weap != NULL) {
				canWield = true;
				break;
			}
		}
		if (canWield) {
			return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Weapon*>(i)!=NULL;},
												[] (Item* i, PlayerChar* p, Level* l) {
													return new QuickWield(p, l, i);
												},
												true);
		} else {
			player->appendLog("You have nothing you can wield");
		}
	}
	// stow weapon
	if (key.c == 'S') {
		auto weap = player->getWeapon();
		// check for curses TODO
		if (weap != NULL) {
			player->appendLog("You stow the " + weap->getDisplayName());
			player->removeWeapon();
			player->getInventory().add(*weap);
		} else {
			player->appendLog("you are not wielding anything");
		}
	}
	// throw item
	if (key.c == 't') {
		bool canThrow = false;
		for (auto pair : player->getInventory().getContents()) {
			if (pair.second.front()->isThrowable()) {
				canThrow = true;
				break;
			}
		}
		if (canThrow) {
			return new ThrowDirectionState(player, level);
		} else {
			player->appendLog("You have nothing you can throw");
		}
	}
	// eat food
	if (key.c == 'e') {
		bool canEat = false;
		for (auto pair : player->getInventory().getContents()) {
			auto food = dynamic_cast<Food*>(pair.second.front());
			if (food != NULL) {
				canEat = true;
				break;
			}
		}
		if (canEat) {
			return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Food*>(i) != NULL;},
												[] (Item* i, PlayerChar* p, Level* l) {
													return new QuickEat(p, l, i);
												},
												true);
		} else {
			player->appendLog("You have nothing you can eat");
		}
	}
	if (key.c == '<' || key.c == '>') {
		for (Feature* feat : level->getFeatures()) {
			Stairs* stair = dynamic_cast<Stairs*>(feat);
			if (stair != NULL) {
				if ((key.c == '>') == stair->getDirection()) {
					int currDepth = level->getDepth();
					delete level;
					level = new Level(currDepth+1, player);
					level->registerMob(player);
					level->generate();
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
			player->attack((Monster*) mob);
			if (mob->isDead()) {
				level->removeMob(mob);
				player->appendLog("The " + mob->getName() + " died, horribly");
				delete mob;
			}
			level->pushMob(player, TURN_TIME);
		} else if ((*level)[newPos].isPassable()) {
			player->move(newPos);
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
						break;
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

PlayState::~PlayState() {}
