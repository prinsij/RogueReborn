/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: stairs.h
 */ 

#pragma once

#include "coord.h"
#include "feature.h"

class Stairs : public Feature {
	public:
		Stairs(Coord, bool);
		bool getDirection();
	private:
		bool downDirection;
};