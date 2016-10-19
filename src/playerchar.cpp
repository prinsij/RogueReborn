#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"
#include "include/mob.h"
#include "include/playerchar.h"
#include "include/ring.h"
#include "include/weapon.h"

PlayerChar::PlayerChar(Coord location, std::string name)
	: Mob('@', location, name, START_ARMOR, START_EXP, START_LEVEL, START_HP),
	  currentStr(START_STR),
	  foodLife(START_FOOD),
	  gold(START_GOLD),
	  inventory(ItemZone()),
	  itemArmor(NULL),
	  itemRingLeft(NULL),
	  itemRingRight(NULL),
	  itemWeapon(NULL),
	  maxStr(START_STR) {}

void PlayerChar::appendLog(std::string entry) {
	this->log.push_back(entry);
	if (this->log.size() > MAX_LOG) {
		this->log.erase(this->log.begin());
	}
}

void PlayerChar::attack(Mob* mob) {
	std::cout << "PlayerChar Attack\n";

	// TODO

	/*
	if (std::abs(this->location[0] - mob->getLocation[0]) <= 1 && std::abs(this->location[1] - mob->getLocation[1]) <= 1) {
		if (rand() % 2 == 0) {
			mob->hit(2);
		}
	}
	*/
}

void PlayerChar::collectGold(GoldPile* goldpile) {
	std::cout << "PlayerChar Collected " << goldpile->getQuantity() << " Gold\n";
	this->gold += goldpile->getQuantity();
}

bool PlayerChar::dropItem(Item* item) {
	if (this->itemArmor == item || 
		this->itemRingLeft == item ||
		this->itemRingRight == item ||
		this->itemWeapon == item)
		return false;

	std::cout << "PlayerChar Dropped Item " << item->getName() << "\n";

	this->inventory.remove(item);
	return true;
}

void PlayerChar::eat(Food* food) {
	std::cout << "PlayerChar Ate " << food->getName() << "\n";

	food->activate(this);
	this->inventory.remove(food);
}

void PlayerChar::equipArmor(Armor* armor) {
	std::cout << "PlayerChar Equipped Armor " << armor->getName() << "\n";

	this->itemArmor = armor;
	this->armor += armor->getRating();
}

void PlayerChar::equipRingLeft(Ring* ring) {
	std::cout << "PlayerChar Equipped Left Ring " << ring->getName() << "\n";

	this->itemRingLeft = ring;
}

void PlayerChar::equipRingRight(Ring* ring) {
	std::cout << "PlayerChar Equipped Right Ring " << ring->getName() << "\n";

	this->itemRingRight = ring;
}

void PlayerChar::equipWeapon(Weapon* weapon) {
	std::cout << "PlayerChar Equipped Weapon " << weapon->getName() << "\n";

	this->itemWeapon = weapon;
}

int PlayerChar::getGold() {
	return this->gold;
}

std::vector<std::pair<Item*, int> > PlayerChar::getInventory() {
	std::map<std::string, std::pair<Item*, int> > itemMap;
	std::vector<Item*> contents = this->inventory.getContents();
	std::vector<std::pair<Item*, int> > displayContents;

	for (auto itemIt = contents.begin() ; itemIt != contents.end() ; itemIt++) {
		std::string itemName = (*itemIt)->getName();

		auto mapIt = itemMap.find(itemName);

		if (mapIt != itemMap.end()) {
			mapIt->second.second++;
		} else {
			itemMap[itemName] = std::make_pair(*itemIt, 1);
		}
	}

	for (auto mapIt = itemMap.begin() ; mapIt != itemMap.end() ; mapIt++) {
		displayContents.push_back(mapIt->second);
	}

	return displayContents;	
}

std::vector<std::string>& PlayerChar::getLog() {
	return this->log;
}

int PlayerChar::getStrength() {
	return this->currentStr;
}

int PlayerChar::getMaxStrength() {
	return this->maxStr;
}

bool PlayerChar::hasAmulet() {
	return this->inventory.contains("The Amulet of Yendor");
}


int PlayerChar::getSightRadius() {
 	return PlayerChar::SIGHT_RADIUS;
}

void PlayerChar::pickupItem(Item* item) {
	this->inventory.add(*item);
}

void PlayerChar::quaff(Potion* potion, Mob* mob) {
	std::cout << "PlayerChar Quaffed " << potion->getName() << "\n";

	potion->activate(mob);
	this->inventory.remove(potion);
}

void PlayerChar::read(Scroll* scroll, Level* level) {
	std::cout << "PlayerChar Read Scroll " << scroll->getName() << "\n";

	scroll->activate(level);
	this->inventory.remove(scroll);	
}

bool PlayerChar::removeArmor() {
	if (this->itemArmor == NULL) return false; 

	std::cout << "PlayerChar Removed Armor " << this->itemArmor->getName() << "\n";

	this->armor -= this->itemArmor->getRating();
	this->itemArmor = NULL;

	return true;
}

bool PlayerChar::removeRingLeft() {
	if (this->itemRingLeft == NULL) return false; 

	std::cout << "PlayerChar Removed Left Ring " << this->itemRingLeft->getName() << "\n";

	this->itemRingLeft = NULL;

	return true;
}

bool PlayerChar::removeRingRight() {
	if (this->itemRingRight == NULL) return false; 

	std::cout << "PlayerChar Removed Right Ring " << this->itemRingRight->getName() << "\n";

	this->itemRingRight = NULL;

	return true;
}

bool PlayerChar::removeWeapon() {
	if (this->itemWeapon == NULL) return false; 

	std::cout << "PlayerChar Removed Weapon " << this->itemWeapon->getName() << "\n";

	this->itemWeapon = NULL;

	return true;
}

bool PlayerChar::throwItem(Item* item) {
	if (!item->isThrowable()) return false;

	std::cout << "PlayerChar Threw " << item->getName() << "\n";

	// TODO

	return true;
}

bool PlayerChar::zap(Wand* wand, Level* level) {
	if (wand->getCharges() == 0) return false;

	std::cout << "PlayerChar Zapped with Wand " << wand->getName() << "\n";

	wand->activate(level);

	// TODO

	return true;
}

std::vector<std::string>& PlayerChar::getLog() {
	return this->log;
}

void PlayerChar::appendLog(std::string item) {
	this->log.push_back(item);
	if (this->log.size() > MAX_LOG) {
		this->log.erase(this->log.begin());
	}
}

int PlayerChar::getSightRadius() {
	return SIGHT_RADIUS;
}
