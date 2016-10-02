#include "include/goldpile.h"
#include "include/coord.h"

GoldPile::GoldPile(Coord pos, int amount)
	: position(pos)
	, amount(amount)
	{}

Coord GoldPile::getPosition() {
	return position;
}

int GoldPile::getAmount() {
	return amount;
}
