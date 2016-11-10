/**
 * @file food.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Food class
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class PlayerChar;

class Food : public Item {
	public:
		Food(Coord, Item::Context);
		bool activate(PlayerChar*);
};