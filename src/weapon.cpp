#include "include/coord.h"
#include "include/item.h"
#include "include/weapon.h"

Weapon::Weapon(Coord location, Item::Context context, std::string name, std::string pseudoName, unsigned char type, std::pair<int, int> enchantment, bool melee, bool canThrow)
	: Item(')', location, context, "Weapon", name, pseudoName, type, false, canThrow),
	  enchantment(enchantment),
	  melee(melee) {}

bool Weapon::activate(Level* level) {
	return false;
}

int Weapon::getChance() {
	return this->enchantment.first;
}

int Weapon::getDamage() {
	return this->enchantment.second;
}

bool Weapon::isMelee() {
	return this->melee;
}