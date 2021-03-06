/**
 * @file playerchar.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the PlayerChar class
 */ 

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/debug.h"
#include "include/food.h"
#include "include/globals.h"
#include "include/item.h"
#include "include/level.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/potion.h"
#include "include/ring.h"
#include "include/scroll.h"
#include "include/wand.h"
#include "include/weapon.h"
#include "libtcod/include/libtcod.hpp"

std::map<PlayerChar::Condition, int> PlayerChar::conditions = {};

std::vector<int> PlayerChar::levelExpBounds = {10, 20, 40, 80, 160, 320, 640, 1300, 2600, 5200, 10000, 20000, 40000, 80000, 160000, 320000, 1000000, 3333333, 6666666, 99900000};

std::vector<int> PlayerChar::foodLifeBounds = {300, 150, 20, 0};

PlayerChar::PlayerChar(Coord location, std::string name)
	: Mob('@', location, name, START_ARMOR, START_EXP, START_HP, START_LEVEL, TCODColor::yellow),
	  currentStr(START_STR),
	  foodLife(START_FOOD),
	  foodStatus(PlayerChar::FULL),
	  gold(START_GOLD),
	  inventory(ItemZone()),
	  itemArmor(NULL),
	  itemRingLeft(NULL),
	  itemRingRight(NULL),
	  itemWeapon(NULL),
	  maxStr(START_STR),
	  moves(0),
	  oocTurns(0)
	{
		PlayerChar::clearConditions();
	}

void PlayerChar::addExp(int exp) {
	this->exp += exp;

	if (this->level <= static_cast<int>(levelExpBounds.size()) && this->exp >= levelExpBounds[this->level - 1]) {
		this->raiseLevel();
	}
}

void PlayerChar::appendLog(std::string entry) {
	this->log.push_back(entry);
	if (this->log.size() > MAX_LOG) {
		this->log.erase(this->log.begin());
	}
}

void PlayerChar::applyCondition(PlayerChar::Condition condition, int turns) {
	if (this->conditions.find(condition) == this->conditions.end()) {
		this->conditions[condition] = turns;
	} else if (this->conditions[condition] > -1) {
		if (turns < 0) {
			this->conditions[condition] += turns;
		}
	}
}

void PlayerChar::attack(Monster* monster) {
	if (this->getLocation().isAdjacentTo(monster->getLocation())) {
		this->oocTurns = 0;

		if (Generator::randPercent() <= this->calculateHitChance(monster)) {
			this->appendLog("You hit the " + monster->getName(this));

			int damage = this->calculateDamage();
			if (!monster->isAwake()) damage += 2;
			else if (monster->hasFlag(Monster::FROZEN)) damage += 1;

			monster->hit(damage);

			if (monster->isDead()) {
				this->appendLog("You have defeated the " + monster->getName(this));
				this->addExp(monster->getExperience());
			}

			if (this->hasCondition(CONFUSE_MONSTER)) {
				monster->addFlag(Monster::CONFUSED);
			}
		} else {
			this->appendLog("You missed the " + monster->getName(this));
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
	//damage += std::get<2>(damageTuple) * std::get<0>(damageTuple);
	damage += std::get<2>(damageTuple);

	// Linear approximation from original Rogue
	damage += static_cast<int>(this->currentStr*0.3133 - 2.7667)/2;

	int miscDamage = this->level + this->dexterity;
	if (this->itemRingLeft != NULL) miscDamage--;
	if (this->itemRingRight != NULL) miscDamage--;
	damage += (miscDamage + 1)/2;

	return damage;
}

int PlayerChar::calculateHitChance(Monster* monster) {
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

	if (monster->hasFlag(Monster::FLYING)) {
		hitChance -= 20;
	}

	return hitChance;
}

void PlayerChar::changeCurrentHP(int amount) {
	this->currentHP += amount;
}

void PlayerChar::changeCurrentStrength(int amount) {
	this->currentStr += amount;
}

void PlayerChar::changeMaxStrength(int amount) {
	this->maxStr += amount;
}

void PlayerChar::changeFoodLife(int amount) {
	this->setFoodLife(this->foodLife + amount);
}

void PlayerChar::clearConditions() {
	PlayerChar::conditions.clear();
}

void PlayerChar::collectGold(GoldPile* goldpile) {
#ifdef DEBUG
	std::cout << "# PlayerChar Collected " << goldpile->getQuantity() << " Gold\n";
#endif
	this->appendLog("Collected " + std::to_string(goldpile->getQuantity()) + " gold");
	this->gold += goldpile->getQuantity();
}

bool PlayerChar::dropItem(Item* item, Level* level) {
	if (this->itemArmor == item ||
		this->itemRingLeft == item ||
		this->itemRingRight == item ||
		this->itemWeapon == item)
		return false;
#ifdef DEBUG
	std::cout << "# PlayerChar Dropped Item " << item->getName() << "\n";
#endif

	this->inventory.remove(item);
	item->setContext(Item::FLOOR);
	item->setLocation(getLocation());
	level->addFeature(item);
	return true;
}

void PlayerChar::dropLevel() {
	this->exp = levelExpBounds[this->level - 2];
	this->level--;
	this->appendLog("Welcome to level " + std::to_string(this->level));

	int deltaHP = Generator::intFromRange(3, 9);
	this->maxHP -= deltaHP;
	this->currentHP = std::min(this->currentHP - deltaHP, this->maxHP);
}

void PlayerChar::eat(Food* food) {
#ifdef DEBUG
	std::cout << "# PlayerChar Ate: " << food->getName() << "\n";
#endif

	food->activate(this);
	this->inventory.remove(food);
}

void PlayerChar::equipArmor(Armor* armor) {
#ifdef DEBUG
	std::cout << "# PlayerChar Equipped Armor: " << armor->getName() << "\n";
#endif

	this->itemArmor = armor;
	this->armor += armor->getRating();
}

void PlayerChar::equipRingLeft(Ring* ring) {
#ifdef DEBUG
	std::cout << "# PlayerChar Equipped Left Ring: " << ring->getName() << "\n";
#endif

	ring->activate(this);
	this->itemRingLeft = ring;
}

void PlayerChar::equipRingRight(Ring* ring) {
#ifdef DEBUG
	std::cout << "# PlayerChar Equipped Right Ring: " << ring->getName() << "\n";
#endif

	ring->activate(this);
	this->itemRingRight = ring;
}

void PlayerChar::equipWeapon(Weapon* weapon) {
#ifdef DEBUG
	std::cout << "# PlayerChar Equipped Weapon: " << weapon->getName() << "\n";
#endif

	this->itemWeapon = weapon;

	weapon->updateName();
}

Armor* PlayerChar::getArmor() {
	return this->itemArmor;
}

int PlayerChar::getDelay() {
	if (this->hasCondition(SLOWED) || this->hasCondition(FAINTING)) {
		return SLOW_TIME;
	} else if (this->hasCondition(HASTED)) {
		return FAST_TIME;
	} else {
		return TURN_TIME;
	}
}

int PlayerChar::getDexterity() {
	return this->dexterity;
}

int PlayerChar::getFoodLife() {
	return this->foodLife;
}

std::string PlayerChar::getFoodStatus() {
	switch(this->foodStatus) {
		case FoodStates::FULL:
			return "";
		case 1:
			return "Hungry";
		case 2:
			return "Weak";
		case 3:
			return "Fainting";
		default:
			return "Starving";
	}
}

int PlayerChar::getGold() {
	return this->gold;
}

float PlayerChar::getSearchChance() {
	return SEARCH_CHANCE + (this->hasCondition(SEARCH) ? SEARCH_CHANCE : 0);
}

int PlayerChar::getSearchRadius() {
	return SEARCH_RADIUS;
}

ItemZone& PlayerChar::getInventory() {
	return this->inventory;
}

int PlayerChar::getLevel() {
	return this->level;
}

std::vector<std::string>& PlayerChar::getLog() {
	return this->log;
}

std::pair<Ring*, Ring*> PlayerChar::getRings() {
	return std::make_pair(this->itemRingLeft, this->itemRingRight);
}


int PlayerChar::getStrength() {
	return this->currentStr;
}

int PlayerChar::getMaxStrength() {
	return this->maxStr;
}

int PlayerChar::getSightRadius() {
 	return PlayerChar::SIGHT_RADIUS;
}

Weapon* PlayerChar::getWeapon() {
	return this->itemWeapon;
}

bool PlayerChar::hasAmulet() {
	return this->inventory.contains("The Amulet of Yendor");
}

bool PlayerChar::hasCondition(PlayerChar::Condition condition) {
	return this->conditions.find(condition) != this->conditions.end();
}

void PlayerChar::hit(int damage) {
	Mob::hit(damage);

	if (this->currentHP > 0 && !this->hasCondition(MAINTAIN_ARMOR) && Generator::randPercent() <= 10) {
		this->armor = std::max(1, this->armor - 1);
	}

	this->oocTurns = 0;
}

bool PlayerChar::move(Coord location, Level* level) {
	if (this->hasCondition(IMMOBILIZED)) {
		this->appendLog("You are being held");
		return false;
	} else if (this->hasCondition(RANDOM_TELEPORTATION) && this->moves % Generator::intFromRange(15, 40) == 0) {
		this->setLocation(level->getRandomEmptyPosition());
		return true;
	}

	// Confusion
	if (this->hasCondition(CONFUSED)) {
		std::vector<Coord> adjacentTiles = level->getAdjPassable(location, true);
		this->setLocation(adjacentTiles[Generator::intFromRange(0, adjacentTiles.size() - 1)]);
		return true;
	}

	this->setLocation(location);

	// Chance to awaken nearby monsters
	for (Mob* mob : level->getMobs()) {
		Monster* monster = dynamic_cast<Monster*>(mob);
		if (monster != NULL && this->location.distanceTo(monster->getLocation())) {
			if (monster && !monster->isAwake()) {
				int wakePercent = static_cast<int>(45/(3 + (this->hasCondition(STEALTHY) ? 1 : 0)));
				monster->setAwake(Generator::randPercent() <= wakePercent);
			}
		}

	}

	return true;
}

bool PlayerChar::pickupItem(Item* item) {
	if (this->inventory.add(*item)) {
		this->appendLog("Picked up " + item->getDisplayName());
		return true;
	}
	return false;
}

void PlayerChar::quaff(Potion* potion, Mob* mob) {
#ifdef DEBUG
	std::cout << "# PlayerChar Quaffed " << potion->getName() << "\n";
#endif

	potion->activate(mob);
	this->inventory.remove(potion);
}

void PlayerChar::raiseLevel() {
	if (this->level <= static_cast<int>(levelExpBounds.size())) {
		this->exp = levelExpBounds[this->level - 1];
		this->level++;
		this->appendLog("Welcome to level " + std::to_string(this->level));
#ifdef DEBUG
		std::cout << "# PlayerChar is now at level " << this->level << "\n";
#endif

		int deltaHP = Generator::intFromRange(3, 9);
		this->currentHP += deltaHP;
		this->maxHP += deltaHP;
	}
}

bool PlayerChar::removeArmor() {
	if (this->itemArmor == NULL) return false;

	if (this->itemArmor->hasEffect(Item::CURSED)) {
		return false;
	}

#ifdef DEBUG
	std::cout << "# PlayerChar Removed Armor " << this->itemArmor->getName() << "\n";
#endif

	this->armor -= this->itemArmor->getRating();
	this->itemArmor = NULL;

	return true;
}

void PlayerChar::removeCondition(PlayerChar::Condition condition) {
	if (this->conditions[condition] < -1) {
		this->conditions[condition] ++;
		return;
	}

	if (this->hasCondition(condition)) {
		if (condition == PlayerChar::BLIND) {
			this->appendLog("The veil of darkness lifts");
		} else if (condition == PlayerChar::HALLUCINATING) {
			this->appendLog("Everything looks SO boring now");
		} else if (condition == PlayerChar::FAINTING) {
			this->appendLog("You can move again");
		} else if (condition == PlayerChar::LEVITATING) {
			this->appendLog("You float gently to the ground");
		}
	}

	this->conditions.erase(condition);
}

bool PlayerChar::removeRingLeft() {
	if (this->itemRingLeft == NULL) return false;

	if (this->itemRingLeft->hasEffect(Item::CURSED)) {
		return false;
	}
#ifdef DEBUG
	std::cout << "# PlayerChar Removed Left Ring " << this->itemRingLeft->getName() << "\n";
#endif

	this->itemRingLeft->deactivate(this);
	this->itemRingLeft = NULL;

	return true;
}

bool PlayerChar::removeRingRight() {
	if (this->itemRingRight == NULL) return false;

	if (this->itemRingRight->hasEffect(Item::CURSED)) {
		return false;
	}

#ifdef DEBUG
	std::cout << "# PlayerChar Removed Right Ring " << this->itemRingRight->getName() << "\n";
#endif

	this->itemRingRight->deactivate(this);
	this->itemRingRight = NULL;

	return true;
}

bool PlayerChar::removeWeapon() {
	if (this->itemWeapon == NULL) return false;

	if (this->itemWeapon->hasEffect(Item::CURSED)) {
		return false;
	}

#ifdef DEBUG
	std::cout << "# PlayerChar Removed Weapon " << this->itemWeapon->getName() << "\n";
#endif

	this->itemWeapon = NULL;

	return true;
}

void PlayerChar::setDexterity(int dexterity) {
	this->dexterity = dexterity;
}

void PlayerChar::setFoodLife(int foodLife) {
	this->foodLife = foodLife;

	int statusWalk = -1;

	for (int i = 0 ; i < static_cast<int>(foodLifeBounds.size()) ; i ++) {
		if (foodLife > foodLifeBounds[i]) {
			statusWalk = i;
			break;
		}
	}

	auto oldStatus = this->foodStatus;
	std::string foodMessage = "You feel ";

	switch(statusWalk) {
		case 0:
			this->foodStatus = FoodStates::FULL;
			foodMessage += "full";
			break;
		case 1:
			this->foodStatus = FoodStates::HUNGRY;
			foodMessage += "hungry";
			break;
		case 2:
			this->foodStatus = FoodStates::WEAK;
			foodMessage += "weak";
			break;
		case 3:
			this->foodStatus = FoodStates::FAINT;
			foodMessage += "like fainting";
			break;
		default:
			this->foodStatus = FoodStates::STARVE;
			foodMessage = "You have starved to death";
			this->dead = true;
			break;
	}

	if (oldStatus != this->foodStatus) {
#ifdef DEBUG
		std::cout << "New Food Message: " << foodMessage << std::endl;
#endif
		this->appendLog(foodMessage);
	}
}

void PlayerChar::setGold(int gold) {
	this->gold = gold;
}

void PlayerChar::setStrength(int strength) {
	this->currentStr = strength;
}

int PlayerChar::update() {
	int foodDecrement = -1;

	if (this->itemRingLeft && this->itemRingRight) {
		foodDecrement = -3;
	} else if (this->itemRingLeft || this->itemRingRight) {
		foodDecrement = -2;
	}

	this->changeFoodLife(this->hasCondition(DIGESTION) ? 0 : foodDecrement);
	this->moves = (this->moves + 1) % MOVES_RESET;

	if (this->oocTurns < MIN_OOC_TURNS)
		this->oocTurns++;

	// Health regeneration
	if (this->oocTurns == MIN_OOC_TURNS) {
		if (this->level < 8) {
			if (this->moves % (21 - this->level*2) == 0) {
				this->currentHP += this->hasCondition(REGENERATION) ? 2 : 1;
				this->currentHP = std::min(this->currentHP, this->maxHP);
			}
		} else {
			if (this->moves % 3 == 0) {
				int upperLimit = this->level - 7;
				if (this->hasCondition(REGENERATION)) upperLimit ++;
				this->currentHP += Generator::intFromRange(1, upperLimit);
				this->currentHP = std::min(this->currentHP, this->maxHP);
			}
		}
	}

	// Update condition counters
	for (auto it = this->conditions.begin() ; it != this->conditions.end() ; it++) {
		if (it->second > -1) {
			it->second--;
		}

		if (it->second == 0) {
			this->removeCondition(it->first);
		}
	}

	if (!this->isDead() && !this->hasCondition(SLEEPING)) {
		if (this->foodStatus == FoodStates::FAINT) {
			if (Generator::intFromRange(0, 20 - this->foodLife) > 0) {
				this->appendLog("You feel very weak.  You faint from the lack of food");
				this->applyCondition(FAINTING, 1);

				if (Generator::randPercent() <= 40) {
					this->foodLife ++;
				}
			}
		}
	}

	return this->getDelay();
}

bool PlayerChar::getSaveFlag() {
	return this->saveFlag;
}

void PlayerChar::setSaveFlag(bool flag) {
	this->saveFlag = flag;
}
