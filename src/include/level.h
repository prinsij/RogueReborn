#pragma once

#include <vector>
#include "coord.h"
#include "terrain.h"
#include "random.h"
#include "playerchar.h"
#include "goldpile.h"
#include "room.h"

class Room;

class Level {
	public:
		Level(int);
		Terrain& tileAt(Coord);
		Coord getSize();
		Terrain& operator[](Coord);
		void generate(PlayerChar);
		bool contains(Coord);
	private:
		const int MAX_ROOMS = 9;
		const double GOLD_CHANCE = .333;
		const Coord SIZE = Coord(80, 25);
		std::vector<std::vector<Terrain> > tiles;
		std::vector<Room> rooms;
		std::vector<Mob> mobs;
		std::vector<GoldPile> golds;
		int genGoldAmount(Generator);
		Coord size;
		int depth;
};
