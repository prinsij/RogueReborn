/**
 * @file tiles.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Corridor, Door, Floor, Wall classes
 */ 

#include "include/terrain.h"
#include "include/tiles.h"

Floor::Floor()
	: Terrain(' ', Terrain::Transparent, Terrain::Passable)
{}

Wall::Wall()
	: Terrain('#', Terrain::Opaque, Terrain::Blocked)
{}

Corridor::Corridor()
	: Terrain('~', Terrain::Corridor, Terrain::Passable)
{}

Door::Door()
	: Terrain('+', Terrain::Corridor, Terrain::Passable)
{}