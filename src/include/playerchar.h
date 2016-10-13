#pragma once

#include <string>
#include "coord.h"
#include "itemzone.h"
#include "mob.h"

class PlayerChar : public Mob {
	public:
		PlayerChar(std::string, Coord);
		int getStrength();
		int getMaxStrength();
		int getArmor();
		int getGold();
		int getLevel();
		bool foundAmulet();
		int maxDelved(); 
	private:
		const int START_HP=10, START_ARMOR=0, START_STR=15, START_GOLD=0, START_LEVEL=1;
		int armor, strength, maxStrength, gold, level;		
		ItemZone backpack;
		bool hasFoundAmulet;
		int maxDepth;
};
