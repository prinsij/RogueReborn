#include "include/item.h"

Item::Item(Location loc, Identified id, Coord coord, std::string name)
	: location(loc)
	, knowledge(id)
	, coord(coord)
	, name(name)
{}

Coord Item::getCoord() {
	return coord;
}

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