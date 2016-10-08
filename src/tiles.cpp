#include "include/tiles.h"
#include "include/terrain.h"

Floor::Floor() 
	: Terrain(' ', Terrain::Transparent, Terrain::Passable)
{}

Wall::Wall()
	: Terrain('#', Terrain::Opaque, Terrain::Blocked)
{}

Corridor::Corridor()
	: Terrain('+', Terrain::Corridor, Terrain::Passable)
{}
