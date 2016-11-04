/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: terrain.h
 */ 

#pragma once

#include "coord.h"

class Coord;

class Terrain {
	public:
		enum Passability {Blocked, Passable};
		enum Visibility {Opaque, Corridor, Transparent};
		enum Mapped {Seen, UnSeen};
		Terrain(char, Visibility, Passability);
		char getSymbol();
		Passability isPassable();
		Mapped isSeen();
		Visibility getVisibility();
		bool checked = false;
		Coord parent;
		void setIsSeen(Mapped);
	private:
		char character;
		Visibility visible;
		Passability passable;
		Mapped seen;
};