#include "include/coord.h"
#include "include/item.h"
#include "include/projectile.h"

Projectile::Projectile(Coord location, Item::Context context, std::string name, unsigned char type, std::pair<int, int> enchantment)
	: Item('*', location, context, name, name, type, true, true),
	  enchantment(enchantment) {}

int Projectile::getChance() {
	return this->enchantment.first;
}

int Projectile::getDamage() {
	return this->enchantment.second;
}
