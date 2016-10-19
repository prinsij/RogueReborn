#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/weapon.h"

Weapon::Weapon(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, std::pair<int, int> enchantment, bool melee, bool canThrow)
	: Item(')', location, context, "Weapon", name, pseudoName, type, false, canThrow),
	  enchantment(enchantment),
	  melee(melee) {}

int Weapon::getChance() {
	return this->enchantment.first;
}

int Weapon::getDamage() {
	return this->enchantment.second;
=======
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
	: Weapon(location, Item::Context::FLOOR, rand() % Weapon::typeVector.size()) {}

Weapon::Weapon(Coord location, Item::Context context, int type)
	: Item(')', location, context, "Weapon", std::get<0>(Weapon::typeVector[type]), type, std::get<3>(Weapon::typeVector[type]), true),
	  damage(std::get<1>(Weapon::typeVector[type])),
	  melee (std::get<2>(Weapon::typeVector[type])) {

	  	this->enchantDamage = (rand() % 3) - 1;
	  	this->enchantHit = (rand() % 3) - 1;
	}

int Weapon::getChance() {
	return this->enchantHit;
}

std::tuple<int, int, int> Weapon::getDamage() {
	return std::make_tuple(this->damage.first, this->damage.second, this->enchantDamage);
>>>>>>> LinkTest
}

bool Weapon::isMelee() {
	return this->melee;
<<<<<<< HEAD
}
=======
}
>>>>>>> LinkTest
