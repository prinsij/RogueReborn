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
#include "include/wand.h"
#include "include/globals.h"
#include "include/ring.h"
#include "include/goldpile.h"
#include "include/helpscreen.h"
#include "include/symbolscreen.h"
#include "include/invscreen.h"
#include "include/item.h"
#include "include/level.h"
#include "include/logscreen.h"
#include "include/monster.h"
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

class RingRemovePrompt : public PlayState {
	public:
		RingRemovePrompt(PlayerChar* player, Level* level)
			: PlayState(player, level)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			if (key.c == 'r' || key.c == 'R') {
				auto ring = player->getRings().second;
				if (player->removeRingRight()) {
					player->getInventory().add(*ring);
					player->appendLog("You take off the " + ring->getDisplayName());
				}
				return new PlayState(player, level);
			}
			if (key.c == 'l' || key.c == 'L') {
				auto ring = player->getRings().first;
				if (player->removeRingLeft()) {
					player->getInventory().add(*ring);
					player->appendLog("You take off the " + ring->getDisplayName());
				}
				return new PlayState(player, level);
			}
			return this;
		}

		virtual void draw(TCODConsole* con) {
			PlayState::draw(con);
			con->print(PROMPTX, PROMPTY, std::string("Which ring to remove (R/L) ?").c_str());
		}
};

class QuickZap : public PlayState {
	public:
		QuickZap(PlayerChar* player, Level* level, Item* item, Coord direction)
			: PlayState(player, level)
			, wand(dynamic_cast<Wand*>(item))
			, direction(direction)
		{
			assert (direction != Coord(0,0));
		}
		virtual UIState* handleInput(TCOD_key_t key) {
			if (wand == NULL) {
				assert (false && "tried to zap non-wand");
				return new PlayState(player, level);
			}
			Coord newLoc = player->getLocation();
			while (true) {
				Coord next = newLoc+direction;
				auto mob = level->monsterAt(next);
				if (mob != NULL) {
					wand->activate(level, mob);
					player->appendLog("You zap with the " + wand->getName());
					if (wand->getCharges() <= 0) {
						player->getInventory().remove(wand);
						player->appendLog("Drained of magic, the wand crumbles to dust");
						delete wand;
					}
					break;
				} else if (!level->contains(next)) {
					assert(false && "zapped out of bounds somehow");
					break;
				} else if ((*level)[next].isPassable() != Terrain::Passable) {
					wand->activate(level, NULL);
					player->appendLog("The wand charge fizzles against a wall");
					break;
				}
				newLoc += direction;
			}
			return new PlayState(player, level);
		}
	private:
		Wand* wand;
		Coord direction;
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

template<typename T>
class QuickUse : public PlayState {
	public:
		QuickUse<T>(PlayerChar* player, Level* level, Item* item,
					std::function<UIState*(T*)> makeUseOf, bool del=true)
			: PlayState(player, level)
			, item(item)
			, makeUseOf(makeUseOf)
			, deleteAfter(del)
		{}

		virtual UIState* handleInput(TCOD_key_t key) {
			T* usable = dynamic_cast<T*>(item);
			if (usable != NULL) {
				auto nextState = makeUseOf(usable);
				player->getInventory().remove(usable);
				if (deleteAfter) delete usable;
				return nextState;
			} else {
				assert (false && "attempted to activate non-activatable");
			}
			return new PlayState(player, level);
		}
	private:
		Item* item;
		std::function<UIState*(T*)> makeUseOf;
		bool deleteAfter;
};

class DirectionPrompt : public PlayState {
	public:
		DirectionPrompt(PlayerChar* player, Level* level, std::function<UIState*(Coord)> makeUseOf)
			: PlayState(player, level)
			, makeUseOf(makeUseOf)
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
				return makeUseOf(direction);
				;

			}
			return this;
		}
	private:
		std::function<UIState*(Coord)> makeUseOf;
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
				Feature* featAt = NULL;
				for (Feature* feat : level->getFeatures()) {
					if (feat->getLocation() == mapPos && feat->getVisible()) {
						con->putChar(scrPos[0], scrPos[1], feat->getSymbol());
						featAt = feat;
					}
				}
				if (featAt == NULL) {
					con->setCharForeground(scrPos[0], scrPos[1], terrain.getColor());
				} else {
					con->setCharForeground(scrPos[0], scrPos[1], featAt->getFColor());
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
								con->setCharForeground(scrPos[0], scrPos[1], mob->getFColor());
 								hallucChar = hallucChar < HALLUC_CHARS.size() ? hallucChar+1 : 0;
 							}
 						}
 					} else {
 						for (Mob* mob : level->getMobs()) {

 							Monster* monster = dynamic_cast<Monster*>(mob);

 							if (monster != NULL && !player->hasCondition(PlayerChar::SEE_INVISIBLE) && monster->hasFlag(Monster::INVISIBLE))
 								continue;

 							if (mob->getLocation() == mapPos) {
 								con->putChar(scrPos[0], scrPos[1], mob->getSymbol());
								con->setCharForeground(scrPos[0], scrPos[1], mob->getFColor());
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
								std::function<UIState*(T*)> makeUseOf) {
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
	auto mobs = level->getMobs();
	for (auto it=mobs.begin(); it != mobs.end(); ++it) {
		if ((*it)->isDead()) {
			if (*it == player) {
				return new RIPScreen(player, level, "Unknown");
			}
			player->appendLog("The " + (*it)->getName() + " dies, horribly");
			level->removeMob(*it);
		}
	}
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
	int turnTime = 0;
	if (numAIGone > 0) {
		turnTime = player->update();
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
	// view symbol explanations
	if (key.c == '/') {
		return new SymbolScreen(player, level);
	}
	// view log
	if (key.c == 'o') {
		return new LogScreen(player, level);
	}
	// Rest action
	if (key.c == '.') {
		level->pushMob(player, turnTime);
		player->appendLog("You rest briefly");
		player->update();
		return this;
	}
	if (key.c == 's') {
		level->pushMob(player, turnTime);
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
		level->pushMob(player, turnTime);
		return new InvScreen(player, level, [] (Item*) {return true;},
											[] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<Item>(p, l, i,
													[p, l] (Item* i) {
														i->setContext(Item::FLOOR);
														p->getInventory().remove(i);
														i->setLocation(p->getLocation());
														l->addFeature(i);
														return new PlayState(p, l);
													}, 
													false);
												},
												true);
	}
	no_drop:;
	// Quaff
	if (key.c == 'q') {
		auto temp_p = player;
		auto temp_l = level;
		return attemptUse<Potion>("You have nothing you can quaff", 
						[] (Item* i) {return dynamic_cast<Potion*>(i)!=NULL;},
						[temp_p, temp_l] (Potion* p) {
							temp_p->appendLog("You drink the " + p->getName());
							p->activate(temp_p);
							return new PlayState(temp_p, temp_l);
						});
	}
	// Read scroll
	if (key.c == 'r') {
		auto temp_l = level;
		auto temp_p = player;
		return attemptUse<Scroll>("You have nothing you can read",
						[] (Item* i) {return dynamic_cast<Scroll*>(i)!=NULL;},
						[temp_l, temp_p] (Scroll* s) {
							temp_p->appendLog("You read the " + s->getName());
							return std::get<1>(s->activate(temp_l));
						});
	}
	// wield weapon
	if (key.c == 'w') {
		for (auto pair : player->getInventory().getContents()) {
			Weapon* weap = dynamic_cast<Weapon*>(pair.second.front());
			if (weap != NULL) {
				level->pushMob(player, turnTime);
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Weapon*>(i)!=NULL;},
											[] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<Weapon>(p, l, i, 
																		[p, l] (Weapon* w) {
																			p->equipWeapon(w);
																			p->getInventory().remove(w);
																			p->appendLog("You wield the " + w->getName());
																			return new PlayState(p, l);
																		}, false);
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
				level->pushMob(player, turnTime);
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Armor*>(i)!=NULL;},
											[] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<Armor>(p, l, i, 
																		[p, l] (Armor* a) {
																			p->equipArmor(a);
																			p->getInventory().remove(a);
																			p->appendLog("You put on the " + a->getDisplayName());
																			return new PlayState(p, l);
																		}, false);
											},
											true);
			}
		}
		player->appendLog("You have nothing you can wear");
		return this;
	}
	// Take off armor
	if (key.c == 'T') {
		auto armor = player->getArmor();
		// check for curses TODO
		if (armor != NULL) {
			level->pushMob(player, turnTime);
			if (player->removeArmor()) {
				player->getInventory().add(*armor);
				player->appendLog("You take off the " + armor->getDisplayName());
			} else {
				player->appendLog("You cannot remove the " + armor->getDisplayName());
			}
			return this;
		} else {
			player->appendLog("you are not wielding anything");
		}
	}
	// Remove ring
	if (key.c == 'R') {
		auto rings = player->getRings();
		if (rings.first == NULL && rings.second == NULL) {
			player->appendLog("You are not wearing any rings");
			return this;
		}
		level->pushMob(player, turnTime);
		if (rings.first == NULL) {
			auto ring = rings.second;
			if (player->removeRingRight()) {
				player->getInventory().add(*ring);
				player->appendLog("You take off the " + ring->getDisplayName());
			}
		} else if (rings.second == NULL) {
			auto ring = rings.first;
			if (player->removeRingLeft()) {
				player->getInventory().add(*ring);
				player->appendLog("You take off the " + ring->getDisplayName());
			}
		} else {
			return new RingRemovePrompt(player, level);
		}
	}
	if (key.c == 'P') {
		auto rings = player->getRings();
		if (rings.first != NULL && rings.second != NULL) {
			player->appendLog("You have no more fingers");
			return this;
		} else {
			bool hasRing = false;
			for (auto pair : player->getInventory().getContents()) {
				Ring* ring = dynamic_cast<Ring*>(pair.second.front());
				if (ring != NULL) {
					hasRing = true;
				}
			}
			if (!hasRing) {
				player->appendLog("You have nothing to put on your finger(s)");
				return this;
			}
			level->pushMob(player, turnTime);
			if (rings.first == NULL) {
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Ring*>(i)!=NULL;},
											[] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<Ring>(p, l, i, 
																		[p, l] (Ring* r) {
																			p->equipRingLeft(r);
																			p->appendLog("You put on the " + r->getDisplayName());
																			p->getInventory().remove(r);
																			return new PlayState(p, l);
																		}, false);
											},
											true);
			} else {
				return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<Ring*>(i)!=NULL;},
											[] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<Ring>(p, l, i, 
																		[p, l] (Ring* r) {
																			p->equipRingRight(r);
																			p->appendLog("You put on the " + r->getDisplayName());
																			p->getInventory().remove(r);
																			return new PlayState(p, l);
																		}, false);
											},
											true);
			}
		}
	}
	// stow weapon
	if (key.c == 'S') {
		auto weap = player->getWeapon();
		// check for curses TODO
		if (weap != NULL) {
			level->pushMob(player, turnTime);
			if (player->removeWeapon()) {
				player->getInventory().add(*weap);
				player->appendLog("You stow the " + weap->getDisplayName());
			} else {
				player->appendLog("You cannot loosen your grip on the " + weap->getDisplayName());
			}
			return this;
		} else {
			player->appendLog("you are not wielding anything");
		}
	}
	// throw item
	if (key.c == 't') {
		for (auto pair : player->getInventory().getContents()) {
			if (pair.second.front()->isThrowable()) {
				level->pushMob(player, turnTime);
				auto temp_p = player;
				auto temp_l = level;
				return new DirectionPrompt(player, level, [temp_p, temp_l] (Coord direction) {
					return new InvScreen(temp_p, temp_l, [] (Item* i) {return i->isThrowable();},
														[direction] (Item* i, PlayerChar* p, Level* l) {
															return new QuickThrow(p, l, i, direction);
														},
														true);
				});
			}
		}
		player->appendLog("You have nothing you can throw");
		return this;
	}
	if (key.c == 'Z') {
		auto temp_p = player;
		auto temp_l = level;
		for (auto pair : player->getInventory().getContents()) {
			if (dynamic_cast<Wand*>(pair.second.front())!=NULL) {
				return new DirectionPrompt(player, level,
											[temp_p, temp_l] (Coord direction) {
												return new InvScreen(temp_p, temp_l, [] (Item* i) {return dynamic_cast<Wand*>(i)!=NULL;},
																	[direction] (Item* i, PlayerChar* p, Level* l) {
																		return new QuickZap(p, l, i, direction);
																	},
																	true);
												});
			}
		}
		player->appendLog("You have nothing with which to zap");
		return this;
																						
	}
	// eat food
	if (key.c == 'e') {
		auto temp_p = player;
		auto temp_l = level;
		return attemptUse<Food>("You have nothing you can eat",
						[] (Item* i) {return dynamic_cast<Food*>(i)!=NULL;},
						[temp_p, temp_l] (Food* f) {
							temp_p->eat(f);
							return new PlayState(temp_p, temp_l);
						});
	}
	if (key.c == '<' || key.c == '>') {
		for (Feature* feat : level->getFeatures()) {
			Stairs* stair = dynamic_cast<Stairs*>(feat);
			if (stair != NULL) {
				if ((key.c == '>') && stair->getDirection()) {
					int currDepth = level->getDepth();
					delete level;
					level = new Level(currDepth+1, player);
					level->registerMob(player);
					level->generate();
					currRoom = updateMap();
					return this;
				} else if (key.c == '<') {
					if (!stair->getDirection() && player->hasAmulet()) {
						int currDepth = level->getDepth();
						if (currDepth == 0) {
							return new RIPScreen(player, level, VICTORY_STR);
						} else {
							delete level;
							level = new Level(currDepth-1, player);
							level->registerMob(player);
							level->generate();
							currRoom = updateMap();
							return this;
						}
					} else {
						player->appendLog("Some magical force prevents your passage upward.");
					}
				}
			}
		}
	}
	//Arrow controls
	auto newPos = player->getLocation().copy();
	if (key.vk == TCODK_UP || key.c == 'k') {
		newPos -= Coord(0, 1);
	} else if (key.vk == TCODK_DOWN || key.c == 'j') {
		newPos += Coord(0, 1);
	} else if (key.vk == TCODK_LEFT || key.c == 'h') {
		newPos -= Coord(1, 0);
	} else if (key.vk == TCODK_RIGHT || key.c == 'l') {
		newPos += Coord(1, 0);
	} else if (key.c == 'y') {
		newPos += Coord(-1, -1);
	} else if (key.c == 'u') {
		newPos += Coord(1, -1);
	} else if (key.c == 'n') {
		newPos += Coord(1, 1);
	} else if (key.c == 'b') {
		newPos += Coord(-1, 1);
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
			level->pushMob(player, turnTime);
		} else if ((*level)[newPos].isPassable()) {
			player->move(newPos, level);
			level->pushMob(player, turnTime);
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
						auto next = tr->activate(player, level);
						if (next != level) {
							delete level;
							level = next;
							currRoom = NULL;
							currRoom = updateMap();
							return this;
						}
					}
				}
			} while (search);
		}
	}
	return this;
}

PlayState::~PlayState() {}
