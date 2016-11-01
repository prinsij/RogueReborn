#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "goldpile.h"
#include "itemzone.h"
#include "mob.h"

class Level;
class Food;
class Item;
class Ring;
class Weapon;
class Armor;
class Wand;
class Scroll;
class Potion;

class PlayerChar : public Mob {
	public:
		PlayerChar(Coord, std::string);
		void activateItem(Item*);
		void appendLog(std::string);
		void attack(Mob*);
		int calculateDamage();
		void collectGold(GoldPile*);
		bool dropItem(Item*, Level*);
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
		static const int START_ARMOR = 1; 
		static const int START_EXP = 0;
		static const int START_GOLD = 0;
		static const int START_HP = 12;
		static const int START_LEVEL = 1;
		static const int START_STR = 16;
		static const int SIGHT_RADIUS = 1;
		static const int START_FOOD = 1250;		
};
