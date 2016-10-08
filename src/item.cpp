#include "include/item.h"

Item::Item(char symbol, Location loc, Identified id, Coord coord, std::string name)
	: Feature(symbol, coord)
	, location(loc)
	, knowledge(id)
	, name(name)
{}

std::string Item::getName() {
	return name;
}

Item::Location Item::getLocation() {
	return location;
}

Item::Identified Item::isIdentified() {
	return knowledge;
}

bool Item::operator==(const Item& other) const {
	return this == &other;
}
