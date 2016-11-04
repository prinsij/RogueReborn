/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: tiles.h
 */ 

#pragma once

#include "terrain.h"

class Floor : public Terrain {
	public:
		Floor();
};

class Wall : public Terrain {
	public:
		Wall();
};

class Corridor : public Terrain {
	public:
		Corridor();
};

class Door : public Terrain {
	public:
		Door();
};