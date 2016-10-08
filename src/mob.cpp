#include "include/mob.h"
#include "include/coord.h"
#include <string>

Mob::Mob(std::string name, Coord coord, int hp)
	: name(name)
	, coord(coord)
	, HP(hp)
	, maxHP(hp)
{}

int Mob::getHP() {
	return HP;
}

int Mob::getMaxHP() {
	return maxHP;
}

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
