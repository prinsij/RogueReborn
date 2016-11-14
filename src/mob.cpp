/**
 * @file mob.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Mob class
 */ 

#include <cmath>
#include <iostream>
#include <string>

#include "include/coord.h"
#include "include/mob.h"

Mob::Mob(char symbol, Coord location)
	: dead(false),
	  location(location),
	  symbol(symbol)
	{}

Mob::Mob(char symbol, Coord location, std::string name, int armor, int exp, int mobHP, int level)
	: armor(armor),
	  currentHP(mobHP),
	  dead(false),
	  exp(exp),
	  level(level),
	  location(location),
	  maxHP(mobHP),
	  name(name),
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

int Mob::getMaxHP() {
	return maxHP;
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

void Mob::hit(int damage) {
	std::cout << this->getName() << " originally had " << this->currentHP << " HP\n";
	int effectiveArmor = 11 - this->armor;
	int deltaHP = std::max(1, static_cast<int>(damage - (damage * 3.00 * effectiveArmor)/100.00));

	this->currentHP -= deltaHP;

	if (this->currentHP <= 0) {
		this->dead = true;
	}
	std::cout << "'" << this->getName() << "' now has " << this->currentHP << " HP after taking " << deltaHP << " damage.\n";
}

bool Mob::isDead() {
	return this->dead;
}

void Mob::moveLocation(Coord location) {
	this->location += location;
}

bool Mob::setCurrentHP(int currentHP) {
	this->currentHP = currentHP;
	return this->currentHP <= 0;
}

void Mob::setLocation(Coord location) {
	this->location = location;
}

void Mob::setMaxHP(int maxHP) {
	this->maxHP = maxHP;
}

int Mob::turn(Level* lvl) {
	return 10000;
}

Mob::~Mob() {}
