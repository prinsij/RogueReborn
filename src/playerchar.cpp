
#include <string>
#include "include/playerchar.h"
#include "include/coord.h"

PlayerChar::PlayerChar(std::string str, Coord pos)
	: Mob(str, '@', pos, START_HP)
	, armor(START_ARMOR)
	, strength(START_STR)
	, maxStrength(START_STR)
	, gold(START_GOLD)
	, level(START_LEVEL)
	, backpack(ItemZone())
	, hasFoundAmulet(false)
	, maxDepth(1)
	{}

int PlayerChar::getArmor() {
	return armor;
}

int PlayerChar::getStrength() {
	return strength;
}

int PlayerChar::getGold() {
	return gold;
}

int PlayerChar::getLevel() {
	return level;
}

bool PlayerChar::foundAmulet() {
	return hasFoundAmulet;
}

int PlayerChar::maxDelved() {
	return maxDepth;
}
