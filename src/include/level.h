#include <vector>
#include "coord.h"
#include "terrain.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
	public:
		Level(int, int);
		Terrain tileAt(Coord);
		Terrain operator[](Coord);
	private:
		std::vector<std::vector<Terrain> > tiles;
		std::vector<Mob> mobs;
};

#endif
