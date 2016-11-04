/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: tiles.cpp
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