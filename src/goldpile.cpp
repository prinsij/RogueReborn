/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: goldpile.cpp
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