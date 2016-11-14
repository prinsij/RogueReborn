/**
 * @file goldpile.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the GoldPile class
 */ 

#include "include/coord.h"
#include "include/feature.h"
#include "include/goldpile.h"

GoldPile::GoldPile(Coord location, int quantity)
	: Feature('*', location),
	  quantity(quantity) {}

int GoldPile::getQuantity() {
	return this->quantity;
}