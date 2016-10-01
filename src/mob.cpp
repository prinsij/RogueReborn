#include "include/mob.h"
#include "include/coord.h"
#include <string>

Mob::Mob(std::string name, Coord coord)
	: name(name)
	, coord(coord)
{}

Coord& Mob::getCoord() {
	return coord;
}

void Mob::setCoord(Coord newPos) {
	coord = newPos;
}

int& Mob::operator[](int dimension) {
	return coord[dimension];
}

std::string Mob::getName() {
	return name;
}
