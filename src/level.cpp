#include "include/terrain.h"
#include "include/mob.h"
#include <vector>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"
#include "include/playerchar.h"
#include "include/tunnel.h"

Level::Level(int depth) 
	: size(getSize())
	, depth(depth) 
{
	for (auto x=0; x < size[0]; x++) {
		tiles.push_back(std::vector<Terrain>());
		for (auto y=0; y < size[1]; y++) {
			tiles[x].push_back(Wall());
		}
	}
}

Terrain& Level::operator[](Coord coord) {
	return tileAt(coord);
}

Terrain& Level::tileAt(Coord coord) {
	return tiles[coord[0]][coord[1]];
}

bool Level::contains(Coord pos) {
	return pos[0] >= 0 && pos[1] >= 0 && pos[0] < size[0] && pos[1] < size[1]; 
}

int Level::genGoldAmount(Generator gen) {
	return 2 + gen.intFromRange(0, 50 + 10 * depth);
}

void Level::generate(PlayerChar player) {
	Generator gen = Generator();
	Coord maxRoomSize = Coord(size[0]/3, size[1]/3);
	for (auto i=0; i < MAX_ROOMS; i++) {

		//if (gen() > ROOM_MISS_CHANCE){

			//Define upper left corner 
			Coord totalTopLeft = Coord((i%3)*maxRoomSize[0], i/3*maxRoomSize[1]);

			Coord padding = Coord(ROOM_PADDING, ROOM_PADDING);

			Coord legalTopLeft = totalTopLeft + padding;
			Coord legalBottomRight = totalTopLeft + maxRoomSize - padding;

			Coord roomSize = Coord(	gen.intFromRange(MIN_ROOM_DIM, legalBottomRight[0] - legalTopLeft[0]),
									gen.intFromRange(MIN_ROOM_DIM, legalBottomRight[1] - legalTopLeft[1]));

			Coord roomPosition = Coord( gen.intFromRange(legalTopLeft[0], legalBottomRight[0] - roomSize[0]),
										gen.intFromRange(legalTopLeft[1], legalBottomRight[1] - roomSize[1]));

			//Really not sure what the purpose of this line is. Why is this being decided randomly?
			Room::Darkness isDark = gen.intFromRange(0, 10) < depth - 1 ? Room::DARK : Room::LIT;


			Room curRoom = Room(roomPosition, roomPosition + roomSize,
								isDark, Room::WORTHLESS, Room::VISIBLE);

			curRoom.dig(*this);

			//put gold in current room
			if (gen() < GOLD_CHANCE && (!player.foundAmulet() || depth >= player.maxDelved())) {
				Coord goldPos = gen.randPosition(curRoom[0], curRoom[1]);
				int goldAmount = genGoldAmount(gen);
				golds.push_back(GoldPile(goldPos, goldAmount));
			}

			//put monsters in current room
			rooms.push_back(curRoom);
		//}
	}

	//Tunnel digging strat:
		//Create symmetric matrix to say (P -> Q) -> (Q -> P)
		//Establish tunnel connections
		//dig tunnels

	bool symmetric [MAX_ROOMS][MAX_ROOMS];//Take care of non-existent rooms

	for (auto i=0; i < MAX_ROOMS; i++){

		int j;

		//Down
		j = i + 3;
		if (j <= 8){
			addTunnel(i, j, &symmetric[i][j], &symmetric[j][i]);
		}
	}
}

void Level::addTunnel(int i, int j, bool* a, bool* b){
	if (!(*a)){
		*a = true;
		*b = true;
		tunnels.push_back(Tunnel(&rooms[i], &rooms[j]));
	}
}