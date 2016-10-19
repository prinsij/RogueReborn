#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/weapon.h"

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
}

bool Weapon::isMelee() {
	return this->melee;
}