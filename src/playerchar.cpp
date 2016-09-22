
#include <string>
#include "include/playerchar.h"
#include "include/coord.h"


int PlayerChar::getHP() {
	return HP;
}

int PlayerChar::getMaxHP() {
	return maxHP;
}

int PlayerChar::getArmor() {
	return armor;
}

int PlayerChar::getStrength() {
	return strength;
}

int PlayerChar::getGold() {
	return gold;
}

std::string PlayerChar::getName() {
	return name;
}

Coord PlayerChar::getCoord() {
	return coord;
}

int PlayerChar::getLevel() {
	return level;
}
