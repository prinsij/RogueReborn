#include <string>

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"
#include "include/mob.h"
#include "include/playerchar.h"
#include "include/ring.h"
#include "include/weapon.h"

PlayerChar::PlayerChar(std::string name, Coord location)
	: Mob(name, '@', location, START_ARMOR, START_EXP, START_LEVEL, START_HP),
	  currentStr(START_STR),
	  gold(START_GOLD),
	  inventory(ItemZone()),
	  itemArmor(NULL),
	  itemRingLeft(NULL),
	  itemRingRight(NULL),
	  itemWeapon(NULL),
	  maxStr(START_STR) {}

void PlayerChar::addGold(int quantity) {
	this->gold += quantity;
}

void PlayerChar::attack(Mob & mob) {
	// TODO
}

void PlayerChar::dropItem(Item & item) {
	this->inventory.remove(item);
}

void PlayerChar::equipArmor(Armor & armor) {
	this->itemArmor = &armor;
	this->changeArmor(armor.getRating());
}

void PlayerChar::equipRingLeft(Ring & ring) {
	this->itemRingLeft = &ring;
}

void PlayerChar::equipRingRight(Ring & ring) {
	this->itemRingRight = &ring;
}

void PlayerChar::equipWeapon(Weapon & weapon) {
	this->itemWeapon = &weapon;
}

int PlayerChar::getGold() {
	return this->gold;
}

int PlayerChar::getStrength() {
	return this->currentStr;
}

bool PlayerChar::hasAmulet() {
	return this->inventory.contains("The Amulet of Yendor");
}

int PlayerChar::maxDelved() {
	return -1;
}

void PlayerChar::pickupItem(Item & item) {
	this->inventory.add(item);
}

void PlayerChar::removeArmor() {
	this->changeArmor(-this->itemArmor->getRating());
	this->itemArmor = NULL;
}

void PlayerChar::removeRingLeft() {
	this->itemRingLeft = NULL;
}

void PlayerChar::removeRingRight() {
	this->itemRingRight = NULL;
}

void PlayerChar::removeWeapon() {
	this->itemWeapon = NULL;
}

void PlayerChar::throwItem(Item & item) {
	if (!item.isThrowable()) return;

	// TODO
}