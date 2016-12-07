/**
 * @file stairs.h
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Member declarations for the Stairs class
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
