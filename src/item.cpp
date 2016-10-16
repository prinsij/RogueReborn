#include <algorithm>
#include <map>
#include <string>

#include "include/item.h"

std::map<std::string, std::map<unsigned char, bool>> Item::identified;

Item::Item(char symbol, Coord location, Item::Context context, std::string className, std::string name, std::string pseudoName, unsigned char type, bool canStack, bool canThrow)
	: Feature(symbol, location),
	  canStack(canStack),
	  canThrow(canThrow),
	  className(className),
	  context(context),
	  name(name),
	  pseudoName(pseudoName),
	  type(type) {}

bool Item::operator==(const Item& other) const {
	return this->name.compare(other.name) == 0;
}

bool Item::operator<(const Item& other) const {
	return this->name.compare(other.name) < 0;
}

Item::Context Item::getContext() {
	return this->context;
}

std::string Item::getDisplayName() {
	return identified[this->className][this->type] ? this->name : this->pseudoName;
}

std::string Item::getName() {
	return this->name;
}

unsigned char Item::getType() {
	return this->type;
}

bool Item::isIdentified() {
	return identified[this->className][this->type];
}

bool Item::isStackable() {
	return this->canStack;
}

bool Item::isThrowable() {
	return this->canThrow;
}

void Item::setIdentified(bool newValue) {
	identified[this->className][this->type] = newValue;
}