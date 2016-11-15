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
#include <time.h>

#include "include/feature.h"
#include "include/food.h"
#include "include/potion.h"
#include "include/weapon.h"
#include "include/armor.h"
#include "include/scroll.h"
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
#include "include/trap.h"
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

template<typename T>
class QuickUse : public PlayState {
	public:
		QuickUse<T>(PlayerChar* player, Level* level, Item* item,
					std::function<void(T*)> makeUseOf)
			: PlayState(player, level)
			, item(item)
			, makeUseOf(makeUseOf)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			T* usable = dynamic_cast<T*>(item);
			if (usable != NULL) {
				makeUseOf(usable);
				player->getInventory().remove(usable);
				delete usable;
			} else {
				assert (false && "attempted to activate non-activatable");
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
		std::function<void(T*)> makeUseOf;
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

class QuickWear : public PlayState {
	public:
		QuickWear(PlayerChar* player, Level* level, Item* item)
			: PlayState(player, level)
			, item(item)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			auto armor = dynamic_cast<Armor*>(item);
			if (armor != NULL) {
				player->getInventory().remove(armor);
				player->equipArmor(armor);
			} else {
				assert (false && "tried to wear non-armor");
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
	, currRoom(NULL)
{
	currRoom = updateMap();
}

Room* PlayState::updateMap() {
	for (auto x=-1; x < 2; x++) {
		for (auto y=-1; y < 2; y++) {
			(*level)[player->getLocation()+Coord(x,y)].setIsSeen(Terrain::Seen);
		}
	}
	Room* result = NULL;
	for (auto& room : level->getRooms()) {
		if (room.contains(player->getLocation(), 1)) {
			result = &room;
		}
	}
	bool blinded = (result == NULL 
 		|| result->getDark() == Room::DARK
 		|| player->hasCondition(PlayerChar::BLIND));
	if (!blinded) {
		for (auto x=result->getPosition1()[0]-1; x < result->getPosition2()[0]+2; x++) {
			for (auto y=result->getPosition1()[1]-1; y < result->getPosition2()[1]+2; y++) {
				(*level)[Coord(x,y)].setIsSeen(Terrain::Seen);
			}
		}
	}
	return result;
}

void PlayState::draw(TCODConsole* con) {
	// Draw terrain
	bool blinded = currRoom == NULL 
 		|| currRoom->getDark() == Room::DARK
 		|| player->hasCondition(PlayerChar::BLIND);
 	unsigned int hallucChar = time(NULL) % HALLUC_CHARS.size();
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			Terrain& ter = (*level)[mapPos];
			if (ter.isSeen() == Terrain::Seen) {
				auto scrPos = mapPos.asScreen();
				Terrain& terrain = (*level)[mapPos];
				con->putChar(scrPos[0], scrPos[1], terrain.getSymbol());
				bool hasFeat = false;
				for (Feature* feat : level->getFeatures()) {
					if (feat->getLocation() == mapPos && feat->getVisible()) {
						con->putChar(scrPos[0], scrPos[1], feat->getSymbol());
						hasFeat = true;
					}
				}
				if (!hasFeat) {
					con->setCharForeground(scrPos[0], scrPos[1], terrain.getColor());
				}
				// Previously but not currently seen
				if (mapPos.distanceTo(player->getLocation()) > 1
						&& (blinded || currRoom == NULL || !currRoom->contains(mapPos, 1))) {
					con->setCharForeground(scrPos[0], scrPos[1], terrain.getColor()*.5);
				// Currently in view
				} else {
					if (player->hasCondition(PlayerChar::HALLUCINATING)) {
 						for (Mob* mob : level->getMobs()) {
 							if (mob->getLocation() == mapPos) {
 								con->putChar(scrPos[0], scrPos[1], HALLUC_CHARS[hallucChar]);
 								hallucChar = hallucChar < HALLUC_CHARS.size() ? hallucChar+1 : 0;
 							}
 						}
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
	"  Armor:"+std::to_string(player->getArmorRating())).c_str());
}

template<typename T>
UIState* PlayState::attemptUse(std::string error, std::function<bool(Item*)> filter, 
								std::function<void(T*)> makeUseOf) {
	for (auto pair : player->getInventory().getContents()) {
		if (filter(pair.second.front())) {
			level->pushMob(player, TURN_TIME);
			return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<T*>(i)!=NULL;},
											[makeUseOf] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<T>(p, l, i, makeUseOf);
											},
											true);
		}
	}
	player->appendLog(error);
	return this;
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
	if (key.c == 's') {
		level->pushMob(player, TURN_TIME);
		player->appendLog("You search your surroundings for traps");
		for (Feature* feat : level->getFeatures()) {
			if (!feat->getVisible()
					&& player->getLocation().distanceTo(feat->getLocation())
					   < player->getSearchRadius()
					&& Generator::rand() <= player->getSearchChance()) {
				feat->setVisible(true);
				player->appendLog("You uncover a secret");
			}
		}
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
		level->pushMob(player, TURN_TIME);
		return new InvScreen(player, level, [] (Item*) {return true;},
											[] (Item* i, PlayerChar* p, Level* l) {
													return new QuickDrop(p, l, i);
												},
												false);
	}
	no_drop:;
	// Quaff
	if (key.c == 'q') {
		auto temp = player;
		return attemptUse<Potion>("You have nothing you can quaff", 
						[] (Item* i) {return dynamic_cast<Potion*>(i)!=NULL;},
						[temp] (Potion* p) {p->activate(temp);});
	}
	// Read scroll
	if (key.c == 'r') {
		auto temp = level;
		return attemptUse<Scroll>("You have nothing you can read",
						[] (Item* i) {return dynamic_cast<Scroll*>(i)!=NULL;},
						[temp] (Scroll* s) {s->activate(temp);});
	}
	// wield weapon
	if (key.c == 'w') {
		for (auto pair : player->getInventory().getContents()) {
			Weapon* weap = dynamic_cast<Weapon*>(pair.second.front());
			if (weap != NULL) {
				level->pushMob(player, TURN_TIME);
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Weapon*>(i)!=NULL;},
													[] (Item* i, PlayerChar* p, Level* l) {
														return new QuickWield(p, l, i);
													},
													true);
			}
		}
		player->appendLog("You have nothing you can wield");
		return this;
	}
	// Wear armor
	if (key.c == 'W') {
		for (auto pair : player->getInventory().getContents()) {
			Armor* armor = dynamic_cast<Armor*>(pair.second.front());
			if (armor != NULL) {
				level->pushMob(player, TURN_TIME);
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Armor*>(i)!=NULL;},
													[] (Item* i, PlayerChar* p, Level* l) {
														return new QuickWear(p, l, i);
													},
													true);
			}
		}
		player->appendLog("You have nothing you can wear");
		return this;
	}
	// stow weapon
	if (key.c == 'S') {
		auto weap = player->getWeapon();
		// check for curses TODO
		if (weap != NULL) {
			level->pushMob(player, TURN_TIME);
			player->appendLog("You stow the " + weap->getDisplayName());
			player->removeWeapon();
			player->getInventory().add(*weap);
			return this;
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
			level->pushMob(player, TURN_TIME);
			return new ThrowDirectionState(player, level);
		} else {
			player->appendLog("You have nothing you can throw");
		}
	}
	// eat food
	if (key.c == 'e') {
		auto temp = player;
		return attemptUse<Food>("You have nothing you can eat",
						[] (Item* i) {return dynamic_cast<Food*>(i)!=NULL;},
						[temp] (Food* f) {temp->eat(f);});
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
			player->move(newPos, level);
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

					Trap* tr = dynamic_cast<Trap*>(feat);
					if (tr != NULL){
						tr->activate(player, level);

						Level* oldLevel = level;
						level = level->getBro();
						delete oldLevel;

						currRoom = NULL;
						currRoom = updateMap();
					}
				}
			} while (search);
		}
	}
	return this;
}

PlayState::~PlayState() {}
