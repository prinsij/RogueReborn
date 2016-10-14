#include <iostream>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/monsterdb.h"

Monster::Monster(char symbol, Coord location, MonsterDB::MonsterData monsterData)
	: Mob(monsterData.name, symbol, location, monsterData.armor, monsterData.exp, -1, monsterData.level),
	  carryChance(monsterData.carryChance),
	  damage(monsterData.damage) {

	int hp = this->diceSum(monsterData.hpBounds.first, monsterData.hpBounds.second);
	Mob::setCurrentHP(hp);
	Mob::setMaxHP(hp);
}

void Monster::attack(Mob* mob) {
	std::cout << "Monster " << this->getName() << " Attack\n";

	// TODO

}

int Monster::calculateDamage() {
	std::pair<int, int> damagePair = this->damage[rand() % this->damage.size()];

	return this->diceSum(damagePair.first, damagePair.second);
}

int Monster::getCarryChance() {
	return this->carryChance;
}

int Monster::turn(Level* level) {
	std::cout << "Monster " << this->getName() << "'s Turn\n";

	// TODO

	return 1;
}