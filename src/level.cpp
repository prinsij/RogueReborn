#include "include/terrain.h"
#include "include/mob.h"
#include <vector>
#include "include/tiles.h"
#include "include/level.h"

Level::Level(int width, int height) {
	for (auto x=0; x < width; x++) {
		tiles.push_back(std::vector<Terrain>());
		for (auto y=0; y < height; y++) {
			tiles[x].push_back(Floor());
		}
	}
}

Terrain Level::operator[](Coord coord) {
	return tileAt(coord);
}

Terrain Level::tileAt(Coord coord) {
	return tiles[coord[0]][coord[1]];
}
