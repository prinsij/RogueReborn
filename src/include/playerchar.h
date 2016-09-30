#include <string>
#include "coord.h"
#include "itemzone.h"
#include "mob.h"

#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H

class PlayerChar : Mob {
	public:
		int getStrength();
		int getArmor();
		int getGold();
		int getHP();
		int getMaxHP();
		int getLevel();
		bool foundAmulet();
		int maxDelved(); 
	private:
		int HP;
		int maxHP;
		int armor;
		int strength;
		int gold;
		ItemZone backpack;
		int level;
		bool hasFoundAmulet;
		int maxDepth;
};

#endif
