/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: potion.h
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"
#include "mob.h"

// <Name>
using POTION_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Potion : public Item {
	public:
		Potion(Coord);
		Potion(Coord, Item::Context, int);
		bool activate(Mob*);

	private:
		static std::vector<POTION_TUPLE_TYPE > typeVector;
		static std::vector<std::string> nameVector;
};