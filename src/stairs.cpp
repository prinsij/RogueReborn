/**
 * @file stairs.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the Stairs class
 */ 

#include "include/coord.h"
#include "include/feature.h"
#include "include/stairs.h"

Stairs::Stairs(Coord location, bool stairsDownDirection)
	: Feature('%', location),
	  downDirection(stairsDownDirection) {}

bool Stairs::getDirection() {
	return this->downDirection;
}
