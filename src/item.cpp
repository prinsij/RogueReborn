/**
 * @file item.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the Item class
 */ 

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "include/feature.h"
#include "include/item.h"
#include "include/random.h"

std::map<std::string, std::map<int, bool> > Item::identified;

std::vector<std::string> Item::shuffleNameVector(std::vector<std::string> nameVector) {
	std::random_shuffle(nameVector.begin(), nameVector.end());
	return nameVector;
};

Item::Item(char symbol, Coord location, Item::Context context, std::string className, std::string name, 
			std::string pseudoName, int type, bool canStack, bool canThrow, int weight)
	: Feature(symbol, location, true, Feature::possibleColors[Generator::intFromRange(0, Feature::possibleColors.size()-1)]),
	  canStack(canStack),
	  canThrow(canThrow),
	  className(className),
	  context(context),
	  name(name),
	  pseudoName(pseudoName),
	  type(type),
	  weight(weight) {}

Item::Item(char symbol, Coord location, Item::Context context, std::string className, std::string name, 
			int type, bool canStack, bool canThrow, int weight)
	: Item(symbol, location, context, className, name, name, type, canStack, canThrow, weight) {}

bool Item::operator==(const Item& other) const {
	return this->name.compare(other.name) == 0;
}

bool Item::operator<(const Item& other) const {
	return this->name.compare(other.name) < 0;
}

void Item::applyEffect(Item::Effect effect) {
	this->effects.insert(effect);
}

std::string Item::getClassName() {
	return this->className;
}

Item::Context Item::getContext() {
	return this->context;
}

int Item::getWeight() {
	return this->weight;
}

bool Item::hasEffect(Item::Effect effect) {
	return this->effects.find(effect) != this->effects.end();
}

bool Item::isCursed() {
	return this->hasEffect(Item::CURSED);
}

void Item::setContext(Item::Context newContext) {
	this->context = newContext;
}

std::string Item::getDisplayName() {
	if (Item::identified[this->className].find(this->type) == Item::identified[this->className].end()) {
		return this->pseudoName;
	} else {
		return Item::identified[this->className][this->type] ?  this->name : this->pseudoName ;
	}
}

std::string Item::getName() {
	return this->name;
}

int Item::getType() {
	return this->type;
}

bool Item::isIdentified() {
	return Item::identified[this->className][this->type];
}

bool Item::isStackable() {
	return this->canStack;
}

bool Item::isThrowable() {
	return this->canThrow;
}

void Item::removeEffect(Item::Effect effect) {
	this->effects.erase(effect);
}

void Item::setIdentified(bool newValue) {
	Item::identified[this->className][this->type] = newValue;
}
