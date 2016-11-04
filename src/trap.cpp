/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: trap.cpp
 */ 

#include "include/coord.h"
#include "include/feature.h"
#include "include/trap.h"

Trap::Trap(Coord location, unsigned char type, bool visible)
	: Feature('^', location),
	  type(type),
	  visible(visible) {}

void Trap::activate(Mob* mob) {
	// TODO
}