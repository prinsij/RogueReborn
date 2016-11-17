/**
 * @file monster.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the Monster class
 */ 

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/globals.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/random.h"

const std::vector<TCODColor> Monster::possibleColors = {TCODColor::lightBlue, TCODColor::red, TCODColor::orange,
							TCODColor::green, TCODColor::purple, TCODColor::yellow};

// Monster Template Values
std::map<char, MONSTER_TUPLE_TYPE > Monster::templateMap = {
	{'A', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 0, 0)},  20,  "AU", 5,std::make_pair( 5,8),      "Aquator",std::make_pair( 8,17)}},
	{'B', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 1, 2)},   1,   "F", 1,std::make_pair( 1,8),          "Bat",std::make_pair( 1, 8)}},
	{'C', MONSTER_TUPLE_TYPE { 4, 15,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  25,    "", 4,std::make_pair( 4,8),      "Centaur",std::make_pair( 7,16)}},
	{'D', MONSTER_TUPLE_TYPE {-1,100,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 3,10)},6800,  "ALN",10,std::make_pair(10,8),       "Dragon",std::make_pair(22,30)}},
	{'E', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 2)},   2,   "A", 1,std::make_pair( 1,8),          "Emu",std::make_pair( 1, 7)}},
	{'F', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 0, 0)},  80,   "ANT", 8,std::make_pair( 8,8),"Venus Flytrap",std::make_pair(14,23)}},
	{'G', MONSTER_TUPLE_TYPE { 2, 20,{std::make_pair( 4, 3),
									  std::make_pair( 3, 5),
									  std::make_pair( 4, 3)},2000, "AFR",13,std::make_pair(13,8),      "Griffin",std::make_pair(17,26)}},
	{'H', MONSTER_TUPLE_TYPE { 5,  0,{std::make_pair( 1, 8)},   3,   "A", 1,std::make_pair( 1,8),    "Hobgoblin",std::make_pair( 1, 9)}},
	{'I', MONSTER_TUPLE_TYPE { 9,  0,{std::make_pair( 1, 2)},  15,   "ANZ", 1,std::make_pair( 1,8),  "Ice Monster",std::make_pair( 1,10)}},
	{'J', MONSTER_TUPLE_TYPE { 6, 70,{std::make_pair( 2,12),
									  std::make_pair( 2, 4)},4000,    "",15,std::make_pair(15,8),   "Jabberwock",std::make_pair(21,26)}},
	{'K', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 4)},   1,  "AF", 1,std::make_pair( 1,8),      "Kestral",std::make_pair( 1, 6)}},
	{'L', MONSTER_TUPLE_TYPE { 8,100,{std::make_pair( 1, 2)},  10,   "G", 3,std::make_pair( 3,8),   "Leprechaun",std::make_pair( 6,15)}},
	{'M', MONSTER_TUPLE_TYPE { 2, 40,{std::make_pair( 3, 4),
									  std::make_pair( 3, 4),
									  std::make_pair( 2, 5)}, 200,  "AC", 8,std::make_pair( 8,8),       "Medusa",std::make_pair(18,26)}},
	{'N', MONSTER_TUPLE_TYPE { 9,100,{std::make_pair( 0, 0)},  37,    "", 3,std::make_pair( 3,8),        "Nymph",std::make_pair(10,19)}},
	{'O', MONSTER_TUPLE_TYPE { 6, 15,{std::make_pair( 1, 8)},   5,   "A", 1,std::make_pair( 1,8),          "Orc",std::make_pair( 3,12)}},
	{'P', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 4, 4)}, 120,   "I", 8,std::make_pair( 8,8),      "Phantom",std::make_pair(15,24)}},
	{'Q', MONSTER_TUPLE_TYPE { 2, 30,{std::make_pair( 1, 2),
									  std::make_pair( 1, 2),
									  std::make_pair( 1, 4)},  32,   "A", 3,std::make_pair( 3,8),       "Quagga",std::make_pair( 9,18)}},
	{'R', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 6)},   9,  "AS", 2,std::make_pair( 2,8),  "Rattlesnake",std::make_pair( 4,13)}},
	{'S', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 3)},   1,   "A", 1,std::make_pair( 1,8),        "Snake",std::make_pair( 1,11)}},
	{'T', MONSTER_TUPLE_TYPE { 4, 50,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 2, 6)}, 120,  "AR", 6,std::make_pair( 6,8),        "Troll",std::make_pair(12,21)}},
	{'U', MONSTER_TUPLE_TYPE {-2,  0,{std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 4, 6)}, 190,   "A", 7,std::make_pair( 7,8),      "Ur-Vile",std::make_pair(16,25)}},
	{'V', MONSTER_TUPLE_TYPE { 1, 20,{std::make_pair( 1,10)}, 350, "ADR", 8,std::make_pair( 8,8),      "Vampire",std::make_pair(20,26)}},
	{'W', MONSTER_TUPLE_TYPE { 4,  0,{std::make_pair( 1, 6)},  55,   "V", 5,std::make_pair( 5,8),       "Wraith",std::make_pair(13,22)}},
	{'X', MONSTER_TUPLE_TYPE { 7, 30,{std::make_pair( 3, 4)}, 100,    "", 7,std::make_pair( 7,8),        "Xeroc",std::make_pair(19,26)}},
	{'Y', MONSTER_TUPLE_TYPE { 6, 30,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  50,    "", 4,std::make_pair( 4,8),         "Yeti",std::make_pair(11,20)}},
	{'Z', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 8)},   6,   "A", 2,std::make_pair( 2,8),       "Zombie",std::make_pair( 3,14)}}
};

Monster::Monster(char symbol, Coord location)
	: Mob(symbol, location),
	  chasing(false),
	  frozenTurns(0) {
	auto monsterIt = Monster::templateMap.find(symbol);

	if (monsterIt == Monster::templateMap.end()) {
		throw std::invalid_argument("Invalid 'symbol' parameter in Monster constructor");
	}

	auto monsterTuple = monsterIt->second;

	armor = std::get<0>(monsterTuple);
	carryChance = std::get<1>(monsterTuple);
	damage = std::get<2>(monsterTuple);
	exp = std::get<3>(monsterTuple);

	std::string flagString = std::get<4>(monsterTuple);

	for (auto flagIt = flagString.begin() ; flagIt != flagString.end() ; flagIt++) {
		switch (*flagIt) {
			case 'A':
				flags.insert(AGGRESSIVE);
				break;
			case 'C':
				flags.insert(CONFUSES);
				break;
			case 'D':
				flags.insert(DRAINS_LIFE);
				break;
			case 'F':
				flags.insert(FLYING);
				break;
			case 'G':
				flags.insert(GREEDY);
				break;
			case 'I':
				flags.insert(INVISIBLE);
				break;
			case 'L':
				flags.insert(FLAMES);
				break;
			case 'N':
				flags.insert(RANGED);
				break;
			case 'R':
				flags.insert(REGENERATIVE);
				break;
			case 'S':
				flags.insert(STINGS);
				break;
			case 'T':
				flags.insert(STATIONARY);
				break;
			case 'U':
				flags.insert(RUSTS);
				break;
			case 'V':
				flags.insert(DROPS_LEVEL);
				break;
			case 'Z':
				flags.insert(FREEZES);
				break;
			default:
				std::cout << "Discovered invalid flag '" << *flagIt << "'";
		}
	}
	level = std::get<5>(monsterTuple);

	int hp = diceSum(std::get<6>(monsterTuple).first, std::get<6>(monsterTuple).second) + 3;
	currentHP = hp;
	maxHP = hp;

	name = std::get<7>(monsterTuple);

	awake = Generator::randBool();

	setFColor(possibleColors[Generator::intFromRange(0, possibleColors.size()-1)]);
}

void Monster::addFlag(Monster::Behaviour flag) {
	this->flags.insert(flag);
}

void Monster::addFrozenTurns(int turns) {
	this->frozenTurns += turns;
}

void Monster::aggrevate() {
	this->awake = true;
	this->chasing = true;
}

void Monster::attackConfuse(PlayerChar* player) {
	if (Generator::intFromRange(0, 99) <= 55) {
			player->applyCondition(PlayerChar::CONFUSED, Generator::intFromRange(12, 22));
			player->appendLog("The gaze of the " + this->getName() + " confused you");
	}
}


void Monster::attackDrainLife(PlayerChar* player) {
	if (Generator::intFromRange(0, 99) <= 60 || player->getMaxHP() <= 30 || player->getHP() < 10) return;

	int selection = Generator::intFromRange(1, 3);

	if (selection != 2 || !player->hasCondition(PlayerChar::SUSTAIN_STRENGTH)) {
		player->appendLog("You feel weaker");
	}

	if (selection != 2) {
		player->setMaxHP(player->getMaxHP() - 1);
		player->setCurrentHP(player->getHP() - 1);
	}

	if (selection != 1 && !player->hasCondition(PlayerChar::SUSTAIN_STRENGTH)) {
		int deltaStrength = Generator::randBool() ? 2 : 1;
		player->setStrength(std::max(1, player->getStrength() - deltaStrength));
	}
}


void Monster::attackDropLevel(PlayerChar* player) {
	if (Generator::intFromRange(0, 99) <= 80 || player->getLevel() <= 5) return;

	player->dropLevel();
}


void Monster::attackFreeze(PlayerChar* player) {
	int freezePercent = 99;

	if (Generator::intFromRange(0, 99) <= 12) return;

	freezePercent -= player->getStrength()*3/2;
	freezePercent -= 4*(player->getLevel() + player->getDexterity());
	freezePercent -= player->getArmorRating()*5;
	freezePercent -= player->getMaxHP()/3;

	if (freezePercent > 10) {
		player->applyCondition(PlayerChar::SLEEPING, Generator::intFromRange(4, 8));
		player->appendLog("You are frozen");
	}
}

void Monster::attackRust(PlayerChar* player) {
	Armor* armor = player->getArmor();

	if (armor == NULL || armor->getRating() == 1) return;

	if (!player->hasCondition(PlayerChar::MAINTAIN_ARMOR) && !armor->hasEffect(Item::PROTECTED)) {
		armor->setEnchantment(armor->getEnchantment() - 1);
		player->appendLog("Your armor weakens");
	}
}


void Monster::attackSteal(Level* level) {
	PlayerChar* player = level->getPlayer();

	if (Generator::intFromRange(0, 99) <= 50) {
		if (Generator::intFromRange(0, 99) <= 10) return;

		ItemZone& inventory = player->getInventory();

		std::vector<Item*> playerItems;

		for (auto mapPair : inventory.getContents()) {
			for (auto item : mapPair.second) {
				playerItems.push_back(item);
			}
		}

		if (playerItems.size() == 0) return;

		Item* stolenItem = playerItems[Generator::intFromRange(0, playerItems.size() - 1)];

		inventory.remove(stolenItem);	
		stolenItem->setContext(Item::FLOOR);
		stolenItem->setLocation(getLocation());

		player->appendLog("Your supplies feel lighter");

		std::cout << "Monster attempted to steal " << stolenItem->getName() << "\n";
	
		//delete stolenItem;
	} else {
		if (player->getGold() <= 0 || Generator::intFromRange(0, 99) <= 10) return;

		int stealAmount = std::min(player->getGold(), Generator::intFromRange(10 * player->getLevel(), 30 * player->getLevel()));

		player->setGold(player->getGold() - stealAmount);
		player->appendLog("Your purse feels lighter");
	}

	// level->removeMob(this);
}


void Monster::attackSting(PlayerChar* player) {
	if (player->getStrength() <= 3 || player->hasCondition(PlayerChar::SUSTAIN_STRENGTH)) return;

	int stingChance = 70 - 6 * player->getArmorRating();

	if (Generator::intFromRange(0, 99) <= stingChance) {
		player->appendLog("The " + this->getName() + "'s bite has weakened you");
		player->setStrength(player->getStrength() - 1);
	}
}

void Monster::attack(Level* level) {
	PlayerChar* player = level->getPlayer();

	bool canAttack = this->getLocation().isAdjacentTo(player->getLocation());

	if (this->hasFlag(RANGED)) {
		canAttack = (this->location[0] == player->getLocation()[0] || this->location[1] == player->getLocation()[1]) && this->location.distanceTo(player->getLocation()) <= 4;
	}

	if (canAttack) {
		if (Generator::intFromRange(0, 99) <= this->calculateHitChance(player)) {

			player->appendLog("The " + this->getName(player) + " hit you");
			player->hit(calculateDamage());

			if (!player->isDead() && !this->hasFlag(CANCELLED)) {

				if (this->hasFlag(CONFUSES)) { this->attackConfuse(player); }
				else if (this->hasFlag(DRAINS_LIFE)) { this->attackDrainLife(player); }
				else if (this->hasFlag(DROPS_LEVEL)) { this->attackDropLevel(player); }
				else if (this->hasFlag(FREEZES)) { this->attackFreeze(player); }
				else if (this->hasFlag(RUSTS)) { this->attackRust(player); }
				else if (this->hasFlag(GREEDY)) { this->attackSteal(level); }
				else if (this->hasFlag(STINGS)) { this->attackSting(player); }
			}
		} else {
			player->appendLog("The " + this->getName(player) + " missed you");
		}
	}
}

int Monster::calculateDamage() {
	std::pair<int, int> damagePair = this->damage[Generator::intFromRange(0, this->damage.size() - 1)];

	return this->diceSum(damagePair.first, damagePair.second);
}

int Monster::calculateHitChance(PlayerChar* player) {
	int chance = 40;
	chance += 3*this->level;
	chance -= 2*player->getLevel() + 2*player->getDexterity();

	return chance;
}

int Monster::getArmorRating() {
	return 11 - this->armor;
}

int Monster::getCarryChance() {
	return this->carryChance;
}

int Monster::getDelay() {
	if (this->hasFlag(SLOWED)) {
		return SLOW_TIME;
	} else if (this->hasFlag(HASTED)) {
		return FAST_TIME;
	} else {
		return TURN_TIME;
	}
}

std::string Monster::getName() {
	return Mob::getName();
}

std::string Monster::getName(PlayerChar* player) {
	if (!this->hasFlag(INVISIBLE) || player->hasCondition(PlayerChar::SEE_INVISIBLE)) return Mob::getName();
	else return "Something";
}

std::vector<char> Monster::getSymbolsForLevel(int depth) {
	depth += 1;

	std::vector<char> symbols;

	for (auto monsterIt = Monster::templateMap.begin() ; monsterIt != Monster::templateMap.end() ; monsterIt++) {
		std::pair<int, int> levelRange = std::get<8>(monsterIt->second);

		if (levelRange.first <= depth && depth <= levelRange.second) {
			symbols.push_back(monsterIt->first);
		}
	}

	return symbols;
}

std::vector<char> Monster::getSymbolsForTreasure(int depth) {
	return getSymbolsForLevel(depth);
}

bool Monster::hasFlag(Behaviour flag) {
	return this->flags.find(flag) != this->flags.end();
}

void Monster::hit(int dmgAmount) {
	Mob::hit(dmgAmount);
	this->aggrevate();
}

bool Monster::isAwake() {
	return this->awake;
}

bool Monster::isVisible() {
	return this->hasFlag(INVISIBLE);
}

void Monster::relocate(Level* level) {
	if (this->hasFlag(CONFUSED) && Generator::randBool()) {
		std::vector<Coord> adjacentTiles = level->getAdjPassable(location, true);
		this->location = adjacentTiles[Generator::intFromRange(0, adjacentTiles.size() - 1)];
		return;
	}

	if (this->chasing) {
		//If you are in the same room as the player, go to him

		std::vector<Coord> path = {this->location};
		if (this->location.distanceTo(level->getPlayer()->getLocation()) == 2) {
			std::vector<Coord> adjacentTiles = level->getAdjPassable(this->location, true);

			for (auto it = adjacentTiles.begin() ; it != adjacentTiles.end() ; it ++) {
				if (it->distanceTo(level->getPlayer()->getLocation()) == 1) {
					path.push_back(*it);
				}
			}

			if (path.size() == 1)
				path.push_back(this->location);
		} else {
			path = level->bfsDiag(this->location, level->getPlayer()->getLocation());
		}

		//MAGIC NUMBER
		if (path.size() < 5 || level->canSee(this->location, level->getPlayer()->getLocation())){
			if (level->tileAt(path[1]).isPassable() == Terrain::Passable && !level->monsterAt(path[1])){
				this->location = path[1];
			}
		} else {
			this->chasing = false;
		}
	}

	if (!this->chasing && Generator::intFromRange(0,99) <= 33) {
		bool moved = false;

		if (this->hasFlag(GREEDY)) {
			std::vector<Coord> nextLocation = level->getNearestGold(this->location);

			if (nextLocation.size() > 1) {
				this->setLocation(nextLocation[1]);
				moved = true;
			}
		}

		if (!moved) {
			// Wander around aimlessly
			std::vector<Coord> possibleCoords = level->getAdjPassable(this->location, true);
			if (possibleCoords.size()) {
				Coord newPlace = possibleCoords[Generator::intFromRange(0, possibleCoords.size()-1)];
				this->location = newPlace;
			}
		}
	}
}

void Monster::removeFlag(Monster::Behaviour flag) {
	this->flags.erase(flag);
}

void Monster::setAwake(bool awake) {
	this->awake = awake;
}

void Monster::setVisible(bool visible) {
	this->visible = visible;
}

int Monster::turn(Level* level) {
	if (this->awake && !this->hasFlag(HELD)) {
		if (this->hasFlag(FROZEN)) {
			if (--this->frozenTurns == 0) {
				this->removeFlag(FROZEN);
			}
		} else {
			if (!this->chasing && this->hasFlag(AGGRESSIVE) && level->canSee(this->getLocation(), level->getPlayer()->getLocation())) {
				this->chasing = true;
			}

			if (this->chasing) {
				attack(level);
			}

			if (!this->hasFlag(STATIONARY)) {
				relocate(level);
			}
		}
	}
	return this->getDelay();
}

Monster* Monster::randomMonster() {
	char kind = 'k';
	int i = 1;
	for (auto pair : templateMap) {
		if (Generator::intFromRange(0, i-1) == 0) {
			kind = pair.first;
		}
		++i;
	}
	return new Monster(kind, Coord(0,0));
}
