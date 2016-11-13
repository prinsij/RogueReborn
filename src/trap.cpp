/**
 * @file trap.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Trap class
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