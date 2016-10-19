#include <algorithm>
#include <cmath> 
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/mob.h"
#include "include/monster.h"

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
}

void Monster::attack(Mob* mob) {
	std::cout << "Monster " << this->getName() << " Attack\n";

	// TODO

	/*
	if (std::abs(this->location[0] - mob->getLocation()[0]) <= 1 && std::abs(this->location[1] - mob->getLocation()[1]) <= 1) {
		if (rand() % 2 == 0) {
			mob->hit(1);
		}
	}
	*/
}

int Monster::calculateDamage() {
	std::pair<int, int> damagePair = this->damage[rand() % this->damage.size()];

	return this->diceSum(damagePair.first, damagePair.second);
}

int Monster::getCarryChance() {
	return this->carryChance;
}

std::vector<char> Monster::getSymbolsForLevel(int depth) {
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

int Monster::turn(Level* level) {
	std::cout << "Monster " << this->getName() << "'s Turn\n";

	// TODO
	
	if (level->tileAt(this->location + Coord(1, 0)).isPassable() && rand() % 2 == 0) {
		this->moveLocation(Coord(1, 0));
	}

	if (level->tileAt(this->location + Coord(-1, 0)).isPassable() && rand() % 2 == 0) {
		this->moveLocation(Coord(-1, 0));
	}

	if (level->tileAt(this->location + Coord(0, 1)).isPassable() && rand() % 2 == 0) {
		this->moveLocation(Coord(0, 1));
	}

	if (level->tileAt(this->location + Coord(0, -1)).isPassable() && rand() % 2 == 0) {
		this->moveLocation(Coord(0, -1));
	}

	return 1;
}