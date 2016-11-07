/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: stairs.cpp
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