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

void Monster::attack(Mob & mob) {
	// TODO
}

int Monster::calculateDamage() {
	std::pair<int, int> damagePair = this->damage[rand() % this->damage.size()];

	return this->diceSum(damagePair.first, damagePair.second);
}

int Monster::getCarryChance() {
	return this->carryChance;
}

int Monster::diceSum(int rolls, int faces) {
	int sum = 0;

	for (int roll = 0 ; roll < rolls ; roll++)
		sum += 1 + (rand() % faces);

	return sum;
}