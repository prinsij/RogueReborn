#include "include/mob.h"
#include "include/coord.h"
#include <string>

Mob::Mob(std::string name, Coord coord)
	: name(name)
	, coord(coord)
{}

Coord Mob::getCoord() {
	return coord;
}

std::string Mob::getName() {
	return name;
}
