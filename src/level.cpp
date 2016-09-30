#include "include/terrain.h"
#include "include/mob.h"
#include <vector>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"
#include "include/playerchar.h"

Level::Level(Coord size, int depth) 
	: size(size)
	, depth(depth) 
{
	for (auto x=0; x < size[0]; x++) {
		tiles.push_back(std::vector<Terrain>());
		for (auto y=0; y < size[1]; y++) {
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

int Level::genGoldAmount(Generator gen) {
	return 2 + gen.intFromRange(0, 50 + 10 * depth);
}

void Level::generate(PlayerChar player) {
	Generator gen = Generator();
	Coord maxRoomSize = Coord(size[0]/3, size[1]/3);
	for (auto i=0; i < MAX_ROOMS; i++) {
		// upper left corner of the box this room goes in
		Coord boxTopLeft = Coord((i%3)*maxRoomSize[0]+1, i/3*maxRoomSize[1]);
		Coord roomPosition, roomSize;
		do {
			roomSize = Coord(4+gen.intFromRange(0, maxRoomSize[0]-4), 4+gen.intFromRange(0, maxRoomSize[1]-4));
			Coord positionRand = Coord(gen.intFromRange(0, maxRoomSize[0] - roomSize[0]), gen.intFromRange(0, maxRoomSize[1] - roomSize[1]));
			roomPosition = boxTopLeft + positionRand;
		} while (roomPosition[1] == 0);
		Room curRoom = Room(roomPosition, roomPosition + roomSize);
		//put gold in current room
		if (gen() < GOLD_CHANCE && (!player.foundAmulet() || depth >= player.maxDelved())) {
			Coord goldPos = gen.randPosition(curRoom[0], curRoom[1]);
			int goldAmount = genGoldAmount(gen);
		}
		//put monsters in current room
	}
}
