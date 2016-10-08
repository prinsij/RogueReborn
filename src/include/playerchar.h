#include <string>
#include "coord.h"
#include "itemzone.h"
#include "mob.h"

#ifndef PLAYERCHAR_H
#define PLAYERCHAR_H

class PlayerChar : public Mob {
	public:
		PlayerChar(Coord);
		int getStrength();
		int getMaxStrength();
		int getArmor();
		int getGold();
		int getHP();
		int getMaxHP();
		int getLevel();
		bool foundAmulet();
		int maxDelved(); 
	private:
		const int START_HP=10, START_ARMOR=0, START_STR=1, START_GOLD=0, START_LEVEL=1;
		int HP, maxHP, armor, strength, maxStrength, gold, level;		
		ItemZone backpack;
		bool hasFoundAmulet;
		int maxDepth;
};

#endif
