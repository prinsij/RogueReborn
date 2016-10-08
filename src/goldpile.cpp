#include "include/goldpile.h"
#include "include/coord.h"
#include "include/feature.h"

GoldPile::GoldPile(Coord pos, int amount)
	: Feature('*', pos)
	, amount(amount)
{}

int GoldPile::getAmount() {
	return amount;
}
