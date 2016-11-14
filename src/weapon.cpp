/**
 * @file weapon.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Weapon class
 */ 

#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/random.h"
#include "include/weapon.h"

std::vector<WEAPON_TUPLE_TYPE > Weapon::typeVector = {
	WEAPON_TUPLE_TYPE {"Short Bow", std::make_pair(0, 0), false, false},
	WEAPON_TUPLE_TYPE {"Darts", std::make_pair(1, 1), true, true},
	WEAPON_TUPLE_TYPE {"Arrows", std::make_pair(1, 2), true, true},
	WEAPON_TUPLE_TYPE {"Daggers", std::make_pair(1, 3), true, true},
	WEAPON_TUPLE_TYPE {"Shurikens", std::make_pair(1, 4), true, true},
	WEAPON_TUPLE_TYPE {"Mace", std::make_pair(2, 3), true, false},
	WEAPON_TUPLE_TYPE {"Long Sword", std::make_pair(3, 4), true, false},
	WEAPON_TUPLE_TYPE {"Two-Handed Sword", std::make_pair(4, 5), true, false}
};

Weapon::Weapon(Coord location)
	: Weapon(location, Item::Context::FLOOR, Generator::intFromRange(0, Weapon::typeVector.size() - 1)) {}

Weapon::Weapon(Coord location, Item::Context context, int type)
	: Item(')', location, context, "Weapon", std::get<0>(Weapon::typeVector[type]), type, std::get<3>(Weapon::typeVector[type]), true),
	  damage(std::get<1>(Weapon::typeVector[type])),
	  melee (std::get<2>(Weapon::typeVector[type])) {

	int chance = Generator::intFromRange(1, 96);
	int iterations = Generator::intFromRange(1, 3);
	int increment = 0;

	if (chance <= 16) {
		increment = -1;
		this->cursed = true;
	} else if (chance <= 32) {
		increment = 1;
	}

	for (int i = 0 ; i < iterations ; i ++) {
		if (Generator::randBool()) this->enchantDamage += increment;
		else this->enchantHit += increment;
	}

	this->updateName();
	this->setIdentified(true);
}

int Weapon::getChance() {
	return this->enchantHit;
}

std::tuple<int, int, int> Weapon::getDamage() {
	return std::make_tuple(this->damage.first, this->damage.second, this->enchantDamage);
}

bool Weapon::isMelee() {
	return this->melee;
}

void Weapon::setEnchantments(int enchantHit, int enchantDamage) {
	this->enchantHit = enchantHit;
	this->enchantDamage = enchantDamage;

	this->updateName();
}

void Weapon::updateName() {
	this->name = (this->enchantHit >= 0 ? "+" : "") + std::to_string(this->enchantHit) + "/"
		+ (this->enchantDamage >= 0 ? "+" : "") + std::to_string(this->enchantDamage) + " "
		+ std::get<0>(Weapon::typeVector[this->type]);
}

