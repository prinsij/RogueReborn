/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: amulet.h
 */ 

#pragma once

#include "coord.h"
#include "item.h"

class Amulet : public Item {
	public:
		Amulet(Coord, Item::Context);
};