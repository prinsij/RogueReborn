/**
 * @file playstate.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the PlayState class
 */ 

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <sys/time.h>
#include <time.h>

#include "include/armor.h"
#include "include/controls.h"
#include "include/debug.h"
#include "include/feature.h"
#include "include/food.h"
#include "include/globals.h"
#include "include/goldpile.h"
#include "include/helpscreen.h"
#include "include/invscreen.h"
#include "include/item.h"
#include "include/level.h"
#include "include/logscreen.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/potion.h"
#include "include/ring.h"
#include "include/ripscreen.h"
#include "include/savescreen.h"
#include "include/scroll.h"
#include "include/stairs.h"
#include "include/statusscreen.h"
#include "include/symbolscreen.h"
#include "include/tiles.h"
#include "include/trap.h"
#include "include/uistate.h"
#include "include/wand.h"
#include "include/weapon.h"
#include "include/weapon.h"
#include "include/wizard.h"
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
			con->print(PROMPTX, PROMPTY, QUIT_PROMPT);
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
					if (player->getInventory().add(*ring)) {
						player->appendLog("You take off the " + ring->getDisplayName());
					} else {
						player->equipRingRight(ring);
						player->appendLog(NO_SPACE_LOG);
					}
				} else {
					player->appendLog("The " + ring->getDisplayName() + TIGHTEN_FINGER);
				}
				return new PlayState(player, level);
			}
			if (key.c == 'l' || key.c == 'L') {
				auto ring = player->getRings().first;
				if (player->removeRingLeft()) {
					if (player->getInventory().add(*ring)) {
						player->appendLog("You take off the " + ring->getDisplayName());
					} else {
						player->equipRingLeft(ring);
						player->appendLog(NO_SPACE_LOG);
					}
				} else {
					player->appendLog("The " + ring->getDisplayName() + TIGHTEN_FINGER);
				}
				return new PlayState(player, level);
			}
			return this;
		}

		virtual void draw(TCODConsole* con) {
			PlayState::draw(con);
			con->print(PROMPTX, PROMPTY, HAND_PROMPT);
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
				if (mob != NULL || !level->contains(next)) {
					wand->activate(level, mob);
					player->appendLog("You zap with the " + wand->getName());
					if (wand->getCharges() <= 0) {
						player->getInventory().remove(wand);
						player->appendLog("Drained of magic, the wand crumbles to dust");
						delete wand;
					}
					break;
				} else if ((*level)[next].isPassable() != Terrain::Passable) {
					wand->activate(level, NULL);
					player->appendLog("You zap with the " + wand->getName());
					player->appendLog("The wand charge fizzles against a wall");
					if (wand->getCharges() <= 0) {
						player->getInventory().remove(wand);
						player->appendLog("Drained of magic, the wand crumbles to dust");
						delete wand;
					}
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
						auto pot = dynamic_cast<Potion*>(item);
						if (pot != NULL) {
							pot->activate(mob);
						}
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
			con->print(PROMPTX, PROMPTY, DIRECTION_PROMPT);
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
	bool blinded = currRoom == NULL
		|| currRoom->getDark() == Room::DARK
		|| player->hasCondition(PlayerChar::BLIND);
	bool halluc = player->hasCondition(PlayerChar::HALLUCINATING);
	unsigned int hallucChar = time(NULL) % HALLUC_CHARS.size();
	// Need the time for the hallucination effect
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int milli = tp.tv_sec * 1000 + tp.tv_usec/1000;
	// Iterate over every coordinate in the level
	for (auto x=0; x < level->getSize()[0]; x++) {
		for (auto y=0; y < level->getSize()[1]; y++) {
			auto mapPos = Coord(x, y);
			Terrain& terrain = (*level)[mapPos];
			// Terrain currently or in the past seen
			if (terrain.isSeen() == Terrain::Seen) {
				auto scrPos = mapPos.asScreen();
				Feature* featAt = NULL;
				// Ignore unpassable terrain because there will be no features there
				if (terrain.isPassable() == Terrain::Passable) {
					for (Feature* feat : level->getFeatures()) {
						if (feat->getLocation() == mapPos && feat->getVisible()) {
							con->putChar(scrPos[0], scrPos[1], feat->getSymbol());
							featAt = feat;
							break;
						}
					}
				}
				// No feature here, so render the tile underneath instead
				if (featAt == NULL) {
					con->putChar(scrPos[0], scrPos[1], terrain.getSymbol());
					con->setCharForeground(scrPos[0], scrPos[1], terrain.getColor());
				} else {
					// Render a randomized character if the player is hallucinating
					if (halluc) {
						con->putChar(scrPos[0], scrPos[1], HALLUC_CHARS[hallucChar]);
						hallucChar = hallucChar < HALLUC_CHARS.size() ? hallucChar+1 : 0;
					} else {
						con->setCharForeground(scrPos[0], scrPos[1], featAt->getFColor());
					}
				}
				// Previously but not currently seen
				// so grey it out
				if (mapPos.distanceTo(player->getLocation(), false) > 1
						&& (blinded || currRoom == NULL || !currRoom->contains(mapPos, 1))) {
					con->setCharForeground(scrPos[0], scrPos[1], terrain.getColor()*.5);
				// Currently in view
				// mobs can't be in unpassable terrain, so don't worry about unpassable tiles
				} else if (terrain.isPassable() == Terrain::Passable) {
					// If hallucinating draw a random character and
					// don't care about color
					if (halluc) {
						Mob* mob = level->monsterAt(mapPos);
						if (mob != NULL) {
							Monster* monster = dynamic_cast<Monster*>(mob);
							// If the player doesn't have a special power, we
							// don't render invisible monsters
							if (monster != NULL
									&& !player->hasCondition(PlayerChar::SEE_INVISIBLE) 
									&& monster->hasFlag(Monster::INVISIBLE)) {
								continue;
							}
							con->putChar(scrPos[0], scrPos[1], HALLUC_CHARS[hallucChar]);
							hallucChar = hallucChar < HALLUC_CHARS.size() ? hallucChar+1 : 0;
						}
					// Put the specific mob character, and use their specific color
					} else {
						Mob* mob = level->monsterAt(mapPos);
						if (mob != NULL) {
							Monster* monster = dynamic_cast<Monster*>(mob);
							// If the player doesn't have a special power, we
							// don't render invisible monsters
							if (monster != NULL
									&& !player->hasCondition(PlayerChar::SEE_INVISIBLE) 
									&& monster->hasFlag(Monster::INVISIBLE)) {
								continue;
							}
							con->putChar(scrPos[0], scrPos[1], mob->getSymbol());
							con->setCharForeground(scrPos[0], scrPos[1], mob->getFColor());
						}
					}
				}
				// Two axises of fore/back-ground color, where a cosine
				// wave of color travels.
				if (halluc) {
					con->setCharForeground(scrPos[0], scrPos[1],
											TCODColor::lerp(TCODColor::orange, TCODColor::purple,
															0.5+0.45*std::cos((milli+scrPos[0]*100)/200.0)));
					con->setCharBackground(scrPos[0], scrPos[1],
											TCODColor::lerp(TCODColor::cyan, TCODColor::yellow,
															0.5+0.45*std::cos((milli+scrPos[1]*100)/200.0)));
				}
			}
		}
	}
	// Draw the log
	if (player->getLog().size() > 0) {
		con->print(0, 0, player->getLog().back().c_str());
	}
	// Draw the helpless alert
	if (player->hasCondition(PlayerChar::SLEEPING)) {
		con->print(PROMPTX, PROMPTY, HELPLESS_MSG);
		auto ppos = player->getLocation().asScreen();
		con->setCharForeground(ppos[0], ppos[1], TCODColor::lightBlue);
	}
	// Display the info bar
	const int y = Coord(0, level->getSize()[1]).asScreen()[1]+1;
	std::string starveStr = player->getFoodStatus();
	std::string lvl, hit, str, gld, arm;
	lvl = std::to_string(player->getLevel());
	hit = std::to_string(player->getHP())+"("+std::to_string(player->getMaxHP())+")";
	str = std::to_string(player->getStrength())+"("+std::to_string(player->getMaxStrength())+")";
	gld = std::to_string(player->getGold());
	arm = std::to_string(player->getArmorRating());
	con->print(0, y, (
	"Level:"+lvl+
	"  Hits:"+hit+
	"  Str:"+str+
	"  Gold:"+gld+
	"  Armor:"+arm+
	"     "+starveStr
	).c_str());
}

template<typename T>
UIState* PlayState::attemptUse(std::string error, std::string invPrompt,
								std::function<bool(Item*)> filter,
								std::function<UIState*(T*)> makeUseOf) {
	for (auto pair : player->getInventory().getContents()) {
		if (filter(pair.second.front())) {
			level->pushMob(player, TURN_TIME);
			return new InvScreen(player, level, [] (Item* i) {return dynamic_cast<T*>(i)!=NULL;},
											[makeUseOf] (Item* i, PlayerChar* p, Level* l) {
												return new QuickUse<T>(p, l, i, makeUseOf);
											},
											true,
											invPrompt);
		}
	}
	player->appendLog(error);
	return this;
}

UIState* PlayState::attemptWear(int turnTime) {
	if (player->getArmor() != NULL) {
		player->appendLog(ALREADY_WEAR);
		return this;
	}
	for (auto pair : player->getInventory().getContents()) {
		Armor* armor = dynamic_cast<Armor*>(pair.second.front());
		if (armor != NULL) {
			level->pushMob(player, turnTime);
			return new InvScreen(player, level,
									[] (Item* i) {return dynamic_cast<Armor*>(i)!=NULL;},
									[] (Item* i, PlayerChar* p, Level* l) {
										return new QuickUse<Armor>(p, l, i,
																[p, l] (Armor* a) {
																	p->equipArmor(a);
																	p->getInventory().remove(a);
																	p->appendLog("You put on the " + a->getDisplayName());
																	return new PlayState(p, l);
																}, false);
									},
									true,
									WEAR_PROMPT);
		}
	}
	player->appendLog(NO_WEAR_MSG);
	return this;
}

UIState* PlayState::attemptTakeOff(int turnTime) {
	auto armor = player->getArmor();
	if (armor != NULL) {
		level->pushMob(player, turnTime);
		if (player->removeArmor()) {
			if (player->getInventory().add(*armor)) {
				player->appendLog("You take off the " + armor->getDisplayName());
			} else {
				player->equipArmor(armor);
				player->appendLog(NO_SPACE_LOG);
			}
		} else {
			player->appendLog("You cannot remove the " + armor->getDisplayName());
		}
		return this;
	}
	player->appendLog(NO_TAKE_OFF_MSG);
	return this;
}

UIState* PlayState::attemptRemove(int turnTime) {
	auto rings = player->getRings();
	if (rings.first == NULL && rings.second == NULL) {
		player->appendLog(NO_REMOVE_MSG);
		return this;
	}
	level->pushMob(player, turnTime);
	if (rings.first == NULL) {
		auto ring = rings.second;
		if (player->removeRingRight()) {
			if (player->getInventory().add(*ring)) {
				player->appendLog("You take off the " + ring->getDisplayName());
			} else {
				player->equipRingRight(ring);
				player->appendLog(NO_SPACE_LOG);
			}
		} else {
			player->appendLog("The " + ring->getDisplayName() + TIGHTEN_FINGER);
		}
	} else if (rings.second == NULL) {
		auto ring = rings.first;
		if (player->removeRingLeft()) {
			if (player->getInventory().add(*ring)) {
				player->appendLog("You take off the " + ring->getDisplayName());
			} else {
				player->equipRingLeft(ring);
				player->appendLog(NO_SPACE_LOG);
			}
		} else {
			player->appendLog("The " + ring->getDisplayName() + TIGHTEN_FINGER);
		}
	} else {
		return new RingRemovePrompt(player, level);
	}
	return this;
}

UIState* PlayState::toggleSaveFlag() {
	// The player sets the save flag to indicates
	// they want to save the game at the next level
	// transition
	player->setSaveFlag(!player->getSaveFlag());
	if (player->getSaveFlag()) {
		player->appendLog(SAVE_ON_MSG);
	} else {
		player->appendLog(SAVE_OFF_MSG);
	}
	return this;
}

UIState* PlayState::attemptDrop(int turnTime) {
	if (player->getInventory().getSize() <= 0) {
		player->appendLog(NO_DROP_MSG);
		return this;
	}
	for (auto feat : level->getFeatures()) {
		Item* item = dynamic_cast<Item*>(feat);
		if (item != NULL && item->getLocation() == player->getLocation()) {
			player->appendLog(ALREADY_THERE_MSG);
			return this;
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
											true,
											DROP_PROMPT);
	return this;
}

UIState* PlayState::attemptQuaff(int turnTime) {
	auto temp_p = player;
	auto temp_l = level;
	return attemptUse<Potion>(NO_QUAFF_MSG,
							  QUAFF_PROMPT,
					[] (Item* i) {return dynamic_cast<Potion*>(i)!=NULL;},
					[temp_p, temp_l] (Potion* p) {
						temp_p->appendLog("You drink the " + p->getName());
						p->activate(temp_p);
						return new PlayState(temp_p, temp_l);
					});
}

UIState* PlayState::attemptSearch(int turnTime) {
	level->pushMob(player, turnTime);
	player->appendLog(SEARCH_MSG);
	for (Feature* feat : level->getFeatures()) {
		if (!feat->getVisible()
				&& player->getLocation().distanceTo(feat->getLocation(), false)
				   <= player->getSearchRadius()
				&& Generator::rand() <= player->getSearchChance()) {
			feat->setVisible(true);
			player->appendLog(SECRET_MSG);
		}
	}
	return this;
}

UIState* PlayState::attemptMove(Coord newPos, TCOD_key_t key, int turnTime) {
	auto& tile = level->tileAt(newPos);
	// Player opens doors in their way,
	// and with the shift key can close them
	if (tile.getSymbol() == DOOR_CLOSED) {
		tile.setPassable(Terrain::Passable);
		tile.setSymbol(DOOR_OPEN);
		player->appendLog(OPEN_DOOR_MSG);
		return this;
	} else if (tile.getSymbol() == DOOR_OPEN
				&& key.shift
				&& level->monsterAt(newPos) == NULL) {
		tile.setPassable(Terrain::Blocked);
		tile.setSymbol(DOOR_CLOSED);
		player->appendLog(CLOSE_DOOR_MSG);
		return this;
	}
	// Attack a monster if there is one at the new spot
	Mob* mob = level->monsterAt(newPos);
	if (mob != NULL) {
		player->attack((Monster*) mob);
		if (mob->isDead()) {
			level->removeMob(mob);
			player->appendLog("The " + mob->getName() + " died, horribly");
			delete mob;
		}
		level->pushMob(player, turnTime);
	// Else if the position is open, move there
	} else if ((*level)[newPos].isPassable()) {
		player->move(newPos, level);
		level->pushMob(player, turnTime);
		currRoom = updateMap();
		// Loop over all features at the location
		bool search;
		do {
			search = false;
			for (Feature* feat : level->getFeatures()) {
				if (feat->getLocation() != newPos) {
					continue;
				}
				// Pickup any loose items
				Item* i = dynamic_cast<Item*>(feat);
				if (i != NULL) {
					if (player->pickupItem(i)) {
						level->removeFeature(feat);
						search = true;
						break;
					}
				}
				// Pickup any loose gold
				GoldPile* gp = dynamic_cast<GoldPile*>(feat);
				if (gp != NULL) {
					player->collectGold(gp);
					level->removeFeature(feat);
					delete feat;
					search = true;
					break;
				}
				// Trigger any traps
				Trap* tr = dynamic_cast<Trap*>(feat);
				if (tr != NULL){
					auto next = tr->activate(player, level);
					if (next != level) {
						delete level;
						level = next;
					}
					currRoom = NULL;
					currRoom = updateMap();
					return this;
				}
			}
		} while (search);
	}
	return this;
}

UIState* PlayState::attemptClimb(bool direction) {
	for (Feature* feat : level->getFeatures()) {
		if (feat->getLocation() != player->getLocation()) {
			continue;
		}
		Stairs* stair = dynamic_cast<Stairs*>(feat);
		if (stair != NULL) {
			if (direction && stair->getDirection()) {
				int currDepth = level->getDepth();
				delete level;
				level = new Level(currDepth+1, player);
				level->registerMob(player);
				level->generate();
				currRoom = updateMap();
				player->appendLog("You descend to level " + std::to_string(level->getDepth()));
				if (player->getSaveFlag()) {
					player->setSaveFlag(false);
					return new SaveScreen(player, level);
				} else {
					return new PlayState(player, level);
				}
			} else if (!direction) {
				if (!stair->getDirection() && player->hasAmulet()) {
					int currDepth = level->getDepth();
					if (currDepth == 1) {
						return new RIPScreen(player, level, VICTORY_STR);
					} else {
						delete level;
						level = new Level(currDepth-1, player);
						level->registerMob(player);
						level->generate();
						currRoom = updateMap();
						player->appendLog("You ascend to level " + std::to_string(level->getDepth()));
						if (player->getSaveFlag()) {
							player->setSaveFlag(false);
							return new SaveScreen(player, level);
						} else {
							return new PlayState(player, level);
						}
					}
				} else {
					player->appendLog(NO_ASCEND_MSG);
				}
			}
		}
	}
	return this;
}

UIState* PlayState::attemptEat(int turnTime) {
	auto temp_p = player;
	auto temp_l = level;
	return attemptUse<Food>(NO_EAT_MSG,
							EAT_PROMPT,
					[] (Item* i) {return dynamic_cast<Food*>(i)!=NULL;},
					[temp_p, temp_l, turnTime] (Food* f) {
						temp_p->eat(f);
						temp_l->pushMob(temp_p, turnTime);
						return new PlayState(temp_p, temp_l);
					});
}

UIState* PlayState::attemptZap(int turnTime) {
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
																true,
																ZAP_PROMPT);
											});
		}
	}
	player->appendLog(NO_ZAP_MSG);
	return this;
}

UIState* PlayState::attemptThrow(int turnTime) {
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
													true,
													THROW_PROMPT);
			});
		}
	}
	player->appendLog(NO_THROW_MSG);
	return this;
}

UIState* PlayState::attemptStow(int turnTime) {
	auto weap = player->getWeapon();
	// check for curses TODO
	if (weap != NULL) {
		level->pushMob(player, turnTime);
		if (player->removeWeapon()) {
			if (player->getInventory().add(*weap)) {
				player->appendLog("You stow the " + weap->getDisplayName());
			} else {
				player->equipWeapon(weap);
				player->appendLog(NO_SPACE_LOG);
			}
		} else {
			player->appendLog(LOOSEN_GRIP + weap->getDisplayName());
		}
	} else {
		player->appendLog(NO_STOW_MSG);
	}
	return this;
}

UIState* PlayState::attemptRead(int turnTime) {
	auto temp_l = level;
	auto temp_p = player;
	return attemptUse<Scroll>(NO_READ_MSG,
							  READ_PROMPT,
					[] (Item* i) {return dynamic_cast<Scroll*>(i)!=NULL;},
					[temp_l, temp_p] (Scroll* s) {
						temp_p->appendLog("You read the " + s->getName());
						auto nextState = std::get<1>(s->activate(temp_l));
						auto ps = dynamic_cast<PlayState*>(nextState);
						if (ps != NULL) {
							ps->currRoom = ps->updateMap();
						}
						return nextState;
					});
}

UIState* PlayState::attemptWield(int turnTime) {
	if (player->getWeapon() != NULL) {
		player->appendLog(ALREADY_WIELD);
		return this;
	}
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
										true,
										WIELD_PROMPT);
		}
	}
	player->appendLog(NO_WIELD_MSG);
	return this;
}

UIState* PlayState::attemptPutOn(int turnTime) {
	auto rings = player->getRings();
	if (rings.first != NULL && rings.second != NULL) {
		player->appendLog(FINGER_DEFICIT);
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
			player->appendLog(NO_PUT_MSG);
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
										true,
										PUT_PROMPT);
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
										true,
										PUT_PROMPT);
		}
	}
}

void PlayState::handleWizardry(TCOD_key_t key) {
	if (key.c == '}') {
		int currDepth = level->getDepth();
		if (currDepth == NUM_LEVELS) {
			player->appendLog("You dare not descend deeper into the dungeon");
			return;
		}
		delete level;
		level = new Level(currDepth+1, player);
		level->registerMob(player);
		level->generate();
		currRoom = updateMap();
		player->appendLog("Teleported to level " + std::to_string(level->getDepth()));
	} else if (key.c == '{') {
		int currDepth = level->getDepth();
		if (currDepth <= 1) return;
		delete level;
		level = new Level(currDepth-1, player);
		level->registerMob(player);
		level->generate();
		currRoom = updateMap();
		player->appendLog("Teleported to level " + std::to_string(level->getDepth()));
	} else if (key.c == '&') {
		for (auto mob : level->getMobs()) {
			if (mob != player) {
				mob->hit(1000000);
			}
		}
	} else if (key.c == '%') {
		for (auto x=0; x < level->getSize()[0]; ++x) {
			for (auto y=0; y < level->getSize()[1]; ++y) {
				level->tileAt(Coord(x,y)).setIsSeen(Terrain::Seen);
			}
		}
	} else if (key.c == '*') {
		if (currRoom != NULL) {
			for (auto x=currRoom->getPosition1()[0]; x <= currRoom->getPosition2()[0]; ++x) {
				for (auto y=currRoom->getPosition1()[1]; y <= currRoom->getPosition2()[1]; ++y) {
					int itemType = Generator::intFromRange(0, 5);
					if (itemType == 0) {
						level->addFeature(new GoldPile(Coord(x,y), 42));
					} else if (itemType == 1) {
						level->addFeature(new Potion(Coord(x,y)));
					} else if (itemType == 2) {
						level->addFeature(new Wand(Coord(x,y)));
					} else if (itemType == 3) {
						level->addFeature(new Scroll(Coord(x,y)));
					} else if (itemType == 4) {
						level->addFeature(new Weapon(Coord(x,y)));
					} else if (itemType == 5) {
						level->addFeature(new Armor(Coord(x,y)));
					} else if (itemType == 6) {
						level->addFeature(new Ring(Coord(x,y)));
					}
				}
			}
		}
	} else if (key.c == '@') {
		for (auto feat : level->getFeatures()) {
			if (dynamic_cast<Stairs*>(feat)) {
				player->setLocation(feat->getLocation());
			}
		}
	} else if (key.c == 'L') {
		if (currRoom != NULL) {
			for (auto x=currRoom->getPosition1()[0]; x <= currRoom->getPosition2()[0]; ++x) {
				for (auto y=currRoom->getPosition1()[1]; y <= currRoom->getPosition2()[1]; ++y) {
					if (level->monsterAt(Coord(x,y)) == NULL) {
						level->registerMob(new Monster('L', Coord(x,y)));
					}
				}
			}
		}
	} else if (key.c == '!') {
		for (auto i=0; i < 30; ++i) {
			auto mob = Monster::randomMonster();
			mob->setLocation(level->getRandomEmptyPosition());
			level->registerMob(mob);
		}
	} else if (key.c == 'E') {
		if (currRoom != NULL) {
			Coord randPos;
			int i = 0;
			do {
				randPos = Generator::randPosition(currRoom->getPosition1(),
												  currRoom->getPosition2());
			} while (level->monsterAt(randPos) != NULL && ++i < 30);
			if (i < 30) {
				level->registerMob(new Monster('E', randPos));
			}
		}
	} else if (key.c == '=') {
		for (auto& pair : player->getInventory().getContents()) {
			pair.second.front()->setIdentified(true);
		}
	} else if (key.c == '-') {
		if (currRoom != NULL) {
			for (auto x=currRoom->getPosition1()[0]; x <= currRoom->getPosition2()[0]; ++x) {
				for (auto y=currRoom->getPosition1()[1]; y <= currRoom->getPosition2()[1]; ++y) {
					level->addFeature(Trap::randomTrap(Coord(x,y)));
				}
			}
		}
	}
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
	int difference = 0;
	while (true) {
		auto tuple = level->popTurnClock();
		auto nextUp = std::get<0>(tuple);
		difference += std::get<1>(tuple);
		if (nextUp == player) {
			level->pushMob(player, 0);
			break;
		}
		// Do AI turn
		auto turnTime = nextUp->turn(level);
		if (turnTime != DISAPPEAR_DELAY) {
			level->pushMob(nextUp, turnTime);
		}
		if (player->isDead()) {
			return new RIPScreen(player, level, "Killed by a " + nextUp->getName());
		}
	}
	int turnTime = TURN_TIME;
	if (difference > 0) {
		turnTime = player->update();
		if (player->isDead()) {
			return new RIPScreen(player, level, "Starved to death");
		}
	}
#ifdef URAWIZARD
	handleWizardry(key);
#endif
	// Skip the player's turn if they are sleeping
	if (player->hasCondition(PlayerChar::SLEEPING)) {
		if (key.vk == TCODK_SPACE) {
			level->pushMob(player, turnTime);
		}
		return this;
	}
	// Quitting
	if (key.c == KEYS::QUIT) {
		return new QuitPrompt2(player, level);
	}
	// view inventory
	if (key.c == KEYS::INV) {
		return new InvScreen(player, level, [] (Item*) {return true;},
											[] (Item*, PlayerChar* p, Level* l) {
													return new PlayState(p, l);
												},
											true);
	}
	// view help
	if (key.c == KEYS::HELP) {
		return new HelpScreen(player, level);
	}
	// view symbol explanations
	if (key.c == KEYS::SYMBOLS) {
		return new SymbolScreen(player, level);
	}
	// view log
	if (key.c == KEYS::LOG) {
		return new LogScreen(player, level);
	}
	// view detailed character info
	if (key.c == KEYS::INFO) {
		return new StatusScreen(player, level);
	}
	// Rest action
	if (key.c == KEYS::REST) {
		level->pushMob(player, turnTime);
		player->appendLog(REST_MSG);
		player->update();
		return this;
	}
	// Search for secrets
	if (key.c == KEYS::SEARCH) {
		return attemptSearch(turnTime);
	}
	// set the save flag
	if (key.c == KEYS::TOGGLE_SAVE) {
		return toggleSaveFlag();
	}
	// drop item
	if (key.c == KEYS::DROP) {
		return attemptDrop(turnTime);
	}
	// Quaff
	if (key.c == KEYS::QUAFF) {
		return attemptQuaff(turnTime);
	}
	// Read scroll
	if (key.c == KEYS::READ) {
		return attemptRead(turnTime);
	}
	// wield weapon
	if (key.c == KEYS::WIELD) {
		return attemptWield(turnTime);
	}
	// Wear armor
	if (key.c == KEYS::WEAR) {
		return attemptWear(turnTime);
	}
	// Take off armor
	if (key.c == KEYS::TAKEOFF) {
		return attemptTakeOff(turnTime);
	}
	// Remove ring
	if (key.c == KEYS::REMOVE) {
		return attemptRemove(turnTime);
	}
	// Put on ring
	if (key.c == KEYS::PUT) {
		return attemptPutOn(turnTime);
	}
	// stow weapon
	if (key.c == KEYS::STOW) {
		return attemptStow(turnTime);
	}
	// throw item
	if (key.c == KEYS::THROW) {
		return attemptThrow(turnTime);
	}
	// use a wand
	if (key.c == KEYS::ZAP) {
		return attemptZap(turnTime);
	}
	// eat food
	if (key.c == KEYS::EAT) {
		return attemptEat(turnTime);
	}
	// climb some stairs
	if (key.c == KEYS::ASCEND || key.c == KEYS::DESCEND) {
		return attemptClimb(key.c == KEYS::DESCEND);
	}
	//Arrow/vi controls
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
		return attemptMove(newPos, key, turnTime);
	}
	return this;
}

PlayState::~PlayState() {}
