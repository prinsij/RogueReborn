#pragma once

#include <string>
#include <vector>

#include "armor.h"
#include "coord.h"
#include "food.h"
#include "goldpile.h"
#include "item.h"
#include "itemzone.h"
#include "mob.h"
#include "potion.h"
#include "ring.h"
#include "scroll.h"
#include "weapon.h"
#include "wand.h"

class Level;

class PlayerChar : public Mob {
	public:
		PlayerChar(Coord, std::string);
		void activateItem(Item*);
		void attack(Mob*);
		void collectGold(GoldPile*);
		bool dropItem(Item*);
		void eat(Food*);
		void equipArmor(Armor*);
		void equipRingLeft(Ring*);
		void equipRingRight(Ring*);
		void equipWeapon(Weapon*);
		int getGold();
		std::vector<std::pair<Item*, int> > getInventory();
		int getStrength();
		int getMaxStrength();
		int getSightRadius();
		bool hasAmulet();
		void pickupItem(Item*);
		void quaff(Potion*, Mob*);
		void read(Scroll*, Level*);
		bool removeArmor();
		bool removeRingLeft();
		bool removeRingRight();
		bool removeWeapon();
		bool throwItem(Item*);
		bool zap(Wand*, Level*);
		std::vector<std::string>& getLog();
		void appendLog(std::string);

	private:
		int currentStr;
		int foodLife;
		int gold;
		ItemZone inventory;
		Armor* itemArmor;
		Ring* itemRingLeft;
		Ring* itemRingRight;
		Weapon* itemWeapon;
		std::vector<std::string> log;
		static const int MAX_LOG = 30;
		int maxStr;
		static const int SIGHT_RADIUS = 1;
		static const int START_ARMOR = 1; 
		static const int START_EXP = 0;
		static const int START_FOOD = 1250;
		static const int START_GOLD = 0;
		static const int START_HP = 12;
		static const int START_LEVEL = 1;
		static const int START_STR = 16;		

		bool removeItem(Item*);
};
