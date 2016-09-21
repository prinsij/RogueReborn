#include <string>
#include "coord.h"
#include "itemzone.h"

#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H

class PlayerChar {
	public:
		int getStrength();
		int getArmor();
		std::string getName();
		int getGold();
		int getHP();
		int getMaxHP();
		Coord getCoord();
		int getLevel();
	private:
		int HP;
		int maxHP;
		int armor;
		int strength;
		int gold;
		std::string name;
		Coord coord;
		ItemZone backpack;
		int level;
};

#endif
