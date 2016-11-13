/**
 * @file playerchar.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the PlayerChar class
 */ 

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/food.h"
#include "include/item.h"
#include "include/level.h"
#include "include/mob.h"
#include "include/playerchar.h"
#include "include/potion.h"
#include "include/ring.h"
#include "include/scroll.h"
#include "include/wand.h"
#include "include/weapon.h"

std::vector<int> PlayerChar::levelExpBounds = {10, 20, 40, 80, 160, 320, 640, 1300, 2600, 5200, 10000, 20000, 40000, 80000, 160000, 320000, 1000000, 3333333, 6666666, 99900000};

PlayerChar::PlayerChar(Coord location, std::string name)
	: Mob('@', location, name, START_ARMOR, START_EXP, START_HP, START_LEVEL),
	  currentStr(START_STR),
	  foodLife(START_FOOD),
	  gold(START_GOLD),
	  inventory(ItemZone()),
	  itemArmor(NULL),
	  itemRingLeft(NULL),
	  itemRingRight(NULL),
	  itemWeapon(NULL),
	  maxStr(START_STR) {}

void PlayerChar::addExp(int exp) {
	this->exp += exp;

	if (this->level <= static_cast<int>(levelExpBounds.size()) && this->exp >= levelExpBounds[this->level - 1])
		this->level++;
}

void PlayerChar::appendLog(std::string entry) {
	this->log.push_back(entry);
	if (this->log.size() > MAX_LOG) {
		this->log.erase(this->log.begin());
	}
}

void PlayerChar::attack(Mob* mob) {
	std::cout << "PlayerChar Attack\n";

	if (this->getLocation().isAdjacentTo(mob->getLocation())) {
		if (Generator::intFromRange(0, 99) <= this->calculateHitChance()) {
			this->appendLog("You hit " + mob->getName());

			mob->hit(this->calculateDamage());

			if (mob->isDead()) {
				this->appendLog("You have defeated the " + mob->getName());
				this->addExp(mob->getExperience());
			}
		} else {
			this->appendLog("You miss " + mob->getName());
		}
	}
}

int PlayerChar::calculateDamage() {
	if (this->itemWeapon == NULL) {
		return 0;
	}

	int damage = 0;

	auto damageTuple = this->itemWeapon->getDamage();
	damage += Mob::diceSum(std::get<0>(damageTuple), std::get<1>(damageTuple));
	damage += std::get<2>(damageTuple) * std::get<0>(damageTuple);


	// Linear approximation from original Rogue
	damage += static_cast<int>(this->currentStr*0.3133 - 2.7667);

	int miscDamage = this->level + this->dexterity;
	if (this->itemRingLeft != NULL) miscDamage--;
	if (this->itemRingRight != NULL) miscDamage--;
	damage += (miscDamage + 1)/2;

	return miscDamage;
}

int PlayerChar::calculateHitChance() {
	if (this->itemWeapon == NULL) {
		return 0;
	}

	int hitChance = 40;

	auto damageTuple = this->itemWeapon->getDamage();
	int effectiveDamage = std::get<0>(damageTuple) + std::get<2>(damageTuple);
	hitChance += 3*effectiveDamage;

	hitChance += 2*this->level;
	hitChance += 2*this->dexterity;
	
	if (this->itemRingLeft != NULL) hitChance--;
	if (this->itemRingRight != NULL) hitChance--;

	return hitChance;
}

void PlayerChar::collectGold(GoldPile* goldpile) {
	std::cout << "PlayerChar Collected " << goldpile->getQuantity() << " Gold\n";
	this->appendLog("Collected " + std::to_string(goldpile->getQuantity()) + " gold");
	this->gold += goldpile->getQuantity();
}

bool PlayerChar::dropItem(Item* item, Level* level) {
	if (this->itemArmor == item ||
		this->itemRingLeft == item ||
		this->itemRingRight == item ||
		this->itemWeapon == item)
		return false;

	std::cout << "PlayerChar Dropped Item " << item->getName() << "\n";

	this->inventory.remove(item);
	item->setContext(Item::FLOOR);
	item->setLocation(getLocation());
	level->addFeature(item);
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

ItemZone& PlayerChar::getInventory() {
	return this->inventory;
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
	item->setContext(Item::INVENTORY);
	this->appendLog("Picked up " + item->getDisplayName());
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

void PlayerChar::setDexterity(int dexterity) {
	this->dexterity = dexterity;
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
