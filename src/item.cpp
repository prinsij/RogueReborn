#include <algorithm>
#include <string>

#include "include/item.h"

Item::Item(char symbol, Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, bool canStack, bool canThrow)
	: Feature(symbol, location),
	  canStack(canStack),
	  canThrow(canThrow),
	  context(context),
	  identified(false),
	  name(name),
	  pseudoName(pseudoName),
	  type(type) {}

bool Item::operator==(const Item& other) const {
	return this == &other;
}

bool Item::operator<(const Item& other) const {
	return this->name.compare(other.name) < 0;
}

Item::Context Item::getContext() {
	return this->context;
}

std::string Item::getDisplayName() {
	return this->identified ? this->name : this->pseudoName;
}

bool Item::getIdentified() {
	return this->identified;
}

std::string Item::getName() {
	return this->name;
}

unsigned char Item::getType() {
	return this->type;
}

bool Item::isStackable() {
	return this->canStack;
}

bool Item::isThrowable() {
	return this->canThrow;
}

void Item::setIdentified(bool identified) {
	this->identified = identified;
}