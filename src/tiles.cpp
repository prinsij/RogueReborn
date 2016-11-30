/**
 * @file tiles.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the Corridor, Door, Floor, Wall classes
 */ 

#include "include/terrain.h"
#include "include/tiles.h"
#include "libtcod/include/libtcod.hpp"

Floor::Floor()
	: Terrain('.', Terrain::Transparent, Terrain::Passable, TCODColor::darkGrey)
{}

Wall::Wall()
	: Terrain('#', Terrain::Opaque, Terrain::Blocked)
{}

Corridor::Corridor()
	: Terrain('~', Terrain::Corridor, Terrain::Passable)
{}

Door::Door()
	: Terrain('+', Terrain::Corridor, Terrain::Blocked)
{}
