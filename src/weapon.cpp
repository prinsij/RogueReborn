#include <algorithm>

#include "include/coord.h"
#include "include/item.h"
#include "include/weapon.h"

std::vector<bool> Weapon::identified;

Weapon::Weapon(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, std::pair<int, int> enchantment, bool melee, bool canThrow)
	: Item('*', location, context, name, pseudoName, type, false, canThrow),
	  enchantment(enchantment),
	  melee(melee) {

		Item::setIdentified(this->isIdentified(type));
}

void Weapon::addIdentified(unsigned char type) {
	if (std::find(identified.begin(), identified.end(), type) != identified.end()) {
		identified.push_back(type);
	}
}

int Weapon::getChance() {
	return this->enchantment.first;
}

int Weapon::getDamage() {
	return this->enchantment.second;
}

bool Weapon::isIdentified(unsigned char type) {
	return std::find(identified.begin(), identified.end(), type) != identified.end();
}

bool Weapon::isMelee() {
	return this->melee;
}