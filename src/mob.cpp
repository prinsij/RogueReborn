#include <string>

#include "include/coord.h"
#include "include/mob.h"

Mob::Mob(char symbol, Coord location)
	: location(location),
	  symbol(symbol) {}

Mob::Mob(char symbol, Coord location, std::string name, int armor, int exp, int mobHP, int level)
	: armor(armor),
	  currentHP(mobHP),
	  exp(exp),
	  level(level),
	  maxHP(mobHP),
	  name(name),
	  location(location),
	  symbol(symbol) {}

int Mob::diceSum(int rolls, int faces) {
	int sum = 0;

	for (int roll = 0 ; roll < rolls ; roll++)
		sum += 1 + (rand() % faces);

	return sum;
}

int Mob::getArmor() {
	return armor;
}

int Mob::getExperience() {
	return exp;
}

int Mob::getHP() {
	return currentHP;
}

int Mob::getLevel() {
	return level;
}

Coord& Mob::getLocation() {
	return location;
}

std::string Mob::getName() {
	return name;
}

char Mob::getSymbol() {
	return symbol;
}

void Mob::moveLocation(Coord location) {
	this->location += location;
}

void Mob::setCurrentHP(int currentHP) {
	this->currentHP = currentHP;
}

void Mob::setLocation(Coord location) {
	this->location = location;
}

void Mob::setMaxHP(int maxHP) {
	this->maxHP = maxHP;
}

Mob::~Mob() {}
