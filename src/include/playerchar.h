#pragma once

#include <string>

#include "armor.h"
#include "coord.h"
#include "item.h"
#include "itemzone.h"
#include "mob.h"
#include "ring.h"
#include "weapon.h"

class PlayerChar : public Mob {
	public:
		PlayerChar(std::string, Coord);
		void addGold(int);
		void attack(Mob &);
		void dropItem(Item &);
		void equipArmor(Armor &);
		void equipRingLeft(Ring &);
		void equipRingRight(Ring &);
		void equipWeapon(Weapon &);
		int getGold();
		int getStrength();
		bool hasAmulet();
		int maxDelved();
		void pickupItem(Item &);
		void removeArmor();
		void removeRingLeft();
		void removeRingRight();
		void removeWeapon();
		void throwItem(Item &);

	private:
		int currentStr;
		int gold;
		ItemZone inventory;
		Armor* itemArmor;
		Ring* itemRingLeft;
		Ring* itemRingRight;
		Weapon* itemWeapon;
		int level;
		int maxStr;
		const int START_ARMOR = 1;
		const int START_EXP = 0;
		const int START_GOLD = 0;
		const int START_HP = 12;
		const int START_LEVEL = 1;
		const int START_STR = 16;		
};
