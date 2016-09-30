#include <vector>
#include "coord.h"
#include "terrain.h"
#include "random.h"
#include "playerchar.h"
#include "goldpile.h"

#ifndef LEVEL_H
#define LEVEL_H

class Level {
	public:
		Level(Coord, int);
		Terrain& tileAt(Coord);
		Terrain& operator[](Coord);
		void generate(PlayerChar);
	private:
		const int MAX_ROOMS = 9;
		const double GOLD_CHANCE = .333;
		std::vector<std::vector<Terrain> > tiles;
		std::vector<Mob> mobs;
		std::vector<GoldPile> golds;
		int genGoldAmount(Generator);
		Coord size;
		int depth;
};

#endif
