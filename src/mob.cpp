/**
 * @file mob.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the Mob class
 */ 

#include <cmath>
#include <iostream>
#include <string>

#include "include/coord.h"
#include "include/debug.h"
#include "include/mob.h"

Mob::Mob(char symbol, Coord location)
	: dead(false),
	  location(location),
	  fcolor(TCODColor::white),
	  symbol(symbol)
	{}

Mob::Mob(char symbol, Coord location, std::string name, int armor, int exp, int mobHP, int level, TCODColor color)
	: armor(armor),
	  currentHP(mobHP),
	  dead(false),
	  exp(exp),
	  level(level),
	  location(location),
	  maxHP(mobHP),
	  name(name),
	  fcolor(color),
	  symbol(symbol)
{}

int Mob::diceSum(int rolls, int faces) {
	int sum = 0;

	for (int roll = 0 ; roll < rolls ; roll++)
		sum += 1 + (rand() % faces);

	return sum;
}

int Mob::getArmorRating() {
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

TCODColor Mob::getFColor() {
	return fcolor;
}

void Mob::setFColor(TCODColor newcol) {
	this->fcolor = newcol;
}

void Mob::hit(int damage) {
	int effectiveArmor = this->getArmorRating();
	int deltaHP = std::max(1, static_cast<int>(damage - (damage * 3.00 * effectiveArmor)/100.00));

	this->currentHP -= deltaHP;

#ifdef DEBUG
    std::cout << "# " << this->getName() << " Hit for " << deltaHP << " / " << damage << ". Now at " << currentHP << " HP.\n";
#endif

	if (this->currentHP <= 0) {
		this->dead = true;
	}
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
