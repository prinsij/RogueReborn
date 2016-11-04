/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: goldpile.h
 */ 

#pragma once

#include "coord.h"
#include "feature.h"

class GoldPile : public Feature {
	public:
		GoldPile(Coord, int);
		int getQuantity();
	private:
		int quantity;
};