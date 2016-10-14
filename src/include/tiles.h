#include "terrain.h"

#ifndef TILES_H
#define TiLES_H

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

#endif
