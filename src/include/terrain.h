
#include "coord.h"

#ifndef TERRAIN_H
#define TERRAIN_H

class Coord;

class Terrain {
	public:
		enum Passability {Blocked, Passable};
		enum Visibility {Opaque, Corridor, Transparent};
		Terrain(char, Visibility, Passability); 
		char getSymbol();
		Passability isPassable();
		Visibility getVisibility();
		bool checked = false;
		Coord parent;
	private:
		char character;
		Visibility visible;
		Passability passable;
};

#endif
