/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: item.cpp
 */ 

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "include/item.h"
#include "include/random.h"

std::map<std::string, std::map<int, bool> > Item::identified;

std::vector<std::string> Item::shuffleNameVector(std::vector<std::string> nameVector) {
	std::random_shuffle(nameVector.begin(), nameVector.end());
	return nameVector;
};

Item::Item(char symbol, Coord location, Item::Context context, std::string className, std::string name, std::string pseudoName, int type, bool canStack, bool canThrow)
	: Feature(symbol, location),
	  canStack(canStack),
	  canThrow(canThrow),
	  className(className),
	  context(context),
	  name(name),
	  pseudoName(pseudoName),
	  type(type) {}

Item::Item(char symbol, Coord location, Item::Context context, std::string className, std::string name, int type, bool canStack, bool canThrow)
	: Item(symbol, location, context, className, name, name, type, canStack, canThrow) {}

bool Item::operator==(const Item& other) const {
	return this->name.compare(other.name) == 0;
}

bool Item::operator<(const Item& other) const {
	return this->name.compare(other.name) < 0;
}

Item::Context Item::getContext() {
	return this->context;
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

void Item::setIdentified(bool newValue) {
	Item::identified[this->className][this->type] = newValue;
}