/**
 * @file monster.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Monster class
 */ 

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/globals.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/random.h"

// Monster Template Values
std::map<char, MONSTER_TUPLE_TYPE > Monster::templateMap = {
	{'A', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 0, 0)},  20,  "A", 5,std::make_pair( 5,8),      "Aquator",std::make_pair( 8,17)}},
	{'B', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 1, 2)},   1,  "F", 1,std::make_pair( 1,8),          "Bat",std::make_pair( 1, 8)}},
	{'C', MONSTER_TUPLE_TYPE { 4, 15,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  25,   "", 4,std::make_pair( 4,8),      "Centaur",std::make_pair( 7,16)}},
	{'D', MONSTER_TUPLE_TYPE {-1,100,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 3,10)},6800,  "A",10,std::make_pair(10,8),       "Dragon",std::make_pair(22,30)}},
	{'E', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 2)},   2,  "A", 1,std::make_pair( 1,8),          "Emu",std::make_pair( 1, 7)}},
	{'F', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 0, 0)},  80,  "A", 8,std::make_pair( 8,8),"Venus Flytrap",std::make_pair(14,23)}},
	{'G', MONSTER_TUPLE_TYPE { 2, 20,{std::make_pair( 4, 3),
									  std::make_pair( 3, 5),
									  std::make_pair( 4, 3)},2000,"AFR",13,std::make_pair(13,8),      "Griffin",std::make_pair(17,26)}},
	{'H', MONSTER_TUPLE_TYPE { 5,  0,{std::make_pair( 1, 8)},   3,  "A", 1,std::make_pair( 1,8),    "Hobgoblin",std::make_pair( 1, 9)}},
	{'I', MONSTER_TUPLE_TYPE { 9,  0,{std::make_pair( 1, 2)},  15,  "A", 1,std::make_pair( 1,8),  "Ice Monster",std::make_pair( 1,10)}},
	{'J', MONSTER_TUPLE_TYPE { 6, 70,{std::make_pair( 2,12),
									  std::make_pair( 2, 4)},4000,   "",15,std::make_pair(15,8),   "Jabberwock",std::make_pair(21,26)}},
	{'K', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 4)},   1, "AF", 1,std::make_pair( 1,8),      "Kestral",std::make_pair( 1, 6)}},
	{'L', MONSTER_TUPLE_TYPE { 8,100,{std::make_pair( 1, 2)},  10,  "G", 3,std::make_pair( 3,8),   "Leprechaun",std::make_pair( 6,15)}},
	{'M', MONSTER_TUPLE_TYPE { 2, 40,{std::make_pair( 3, 4),
									  std::make_pair( 3, 4),
									  std::make_pair( 2, 5)}, 200,  "A", 8,std::make_pair( 8,8),       "Medusa",std::make_pair(18,26)}},
	{'N', MONSTER_TUPLE_TYPE { 9,100,{std::make_pair( 0, 0)},  37,   "", 3,std::make_pair( 3,8),        "Nymph",std::make_pair(10,19)}},
	{'O', MONSTER_TUPLE_TYPE { 6, 15,{std::make_pair( 1, 8)},   5,  "A", 1,std::make_pair( 1,8),          "Orc",std::make_pair( 3,12)}},
	{'P', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 4, 4)}, 120,  "I", 8,std::make_pair( 8,8),      "Phantom",std::make_pair(15,24)}},
	{'Q', MONSTER_TUPLE_TYPE { 2, 30,{std::make_pair( 1, 2),
									  std::make_pair( 1, 2),
									  std::make_pair( 1, 4)},  32,  "A", 3,std::make_pair( 3,8),       "Quagga",std::make_pair( 9,18)}},
	{'R', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 6)},   9,  "A", 2,std::make_pair( 2,8),  "Rattlesnake",std::make_pair( 4,13)}},
	{'S', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 3)},   1,  "A", 1,std::make_pair( 1,8),        "Snake",std::make_pair( 1,11)}},
	{'T', MONSTER_TUPLE_TYPE { 4, 50,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 2, 6)}, 120, "AR", 6,std::make_pair( 6,8),        "Troll",std::make_pair(12,21)}},
	{'U', MONSTER_TUPLE_TYPE {-2,  0,{std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 4, 6)}, 190,  "A", 7,std::make_pair( 7,8),      "Ur-Vile",std::make_pair(16,25)}},
	{'V', MONSTER_TUPLE_TYPE { 1, 20,{std::make_pair( 1,10)}, 350, "AR", 8,std::make_pair( 8,8),      "Vampire",std::make_pair(20,26)}},
	{'W', MONSTER_TUPLE_TYPE { 4,  0,{std::make_pair( 1, 6)},  55,   "", 5,std::make_pair( 5,8),       "Wraith",std::make_pair(13,22)}},
	{'X', MONSTER_TUPLE_TYPE { 7, 30,{std::make_pair( 3, 4)}, 100,   "", 7,std::make_pair( 7,8),        "Xeroc",std::make_pair(19,26)}},
	{'Y', MONSTER_TUPLE_TYPE { 6, 30,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  50,   "", 4,std::make_pair( 4,8),         "Yeti",std::make_pair(11,20)}},
	{'Z', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 8)},   6,  "A", 2,std::make_pair( 2,8),       "Zombie",std::make_pair( 3,14)}}
};

Monster::Monster(char symbol, Coord location)
	: Mob(symbol, location) {
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
	std::vector<Behaviour> flagVector;

	for (auto flagIt = flagString.begin() ; flagIt != flagString.end() ; flagIt++) {
		switch (*flagIt) {
			case 'A':
				flagVector.push_back(AGGRESSIVE);
				break;
			case 'F':
				flagVector.push_back(FLYING);
				break;
			case 'G':
				flagVector.push_back(GREEDY);
				break;
			case 'I':
				flagVector.push_back(INVISIBLE);
				break;
			case 'R':
				flagVector.push_back(REGENERATIVE);
				break;
			default:
				std::cout << "Discovered invalid flag '" << *flagIt << "'";
		}
	}

	flags = flagVector;
	level = std::get<5>(monsterTuple);

	int hp = std::get<6>(monsterTuple).first + diceSum(1, std::get<6>(monsterTuple).second) - 1;
	currentHP = hp;
	maxHP = hp;

	name = std::get<7>(monsterTuple);

	awake = Generator::randBool();
	//awake = true;

	chasing = false;
}

void Monster::aggrevate() {
	this->awake = true;
	this->chasing = true;
}

void Monster::attack(Level* level) {
	PlayerChar* player = level->getPlayer();

	if (this->getLocation().isAdjacentTo(player->getLocation())) {
		if (Generator::intFromRange(0, 99) <= this->calculateHitChance(player)) {
			player->appendLog("The " + this->getName() + " hit you");
			player->hit(calculateDamage());
		} else {
			player->appendLog("The " + this->getName() + " missed");
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

int Monster::getCarryChance() {
	return this->carryChance;
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
	return std::find(this->flags.begin(), this->flags.end(), AGGRESSIVE) != this->flags.end();
}

bool Monster::isAwake() {
	return this->awake;
}

void Monster::relocate(Level* level) {

	if (this->chasing) {
		//If you are in the same room as the player, go to him
		std::vector<Coord> path = level->bfsDiag(this->location, level->getPlayer()->getLocation());

		//MAGIC NUMBER
		if (path.size() < 5 || level->canSee(this->location, level->getPlayer()->getLocation())){
			if (level->tileAt(path[1]).isPassable() == Terrain::Passable && !level->monsterAt(path[1])){
				this->location = path[1];	
			}
		} else {
			this->chasing = false;
		}
	}

	if (!this->chasing && Generator::randBool()) {
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
			std::vector<Coord> possibleCoords = level->getAdjPassable(this->location);
			if (possibleCoords.size()) {
				Coord newPlace = possibleCoords[Generator::intFromRange(0, possibleCoords.size()-1)];
				this->location = newPlace;
			}
		}
	}
}

int Monster::turn(Level* level) {
	if (this->awake) {
		if (!this->chasing && this->hasFlag(AGGRESSIVE) && level->canSee(this->getLocation(), level->getPlayer()->getLocation())) {
			this->chasing = true;
		}

		if (this->chasing) {
			attack(level);
		}

		relocate(level);

		//std::cout << this->getName() << " (" << this << ") is at " << location.toString() << std::endl;

	}

	return TURN_TIME;
}
