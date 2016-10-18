#pragma once

#include <vector>
#include <map>
#include <queue>
#include "coord.h"
#include "terrain.h"
#include "random.h"
#include "playerchar.h"
#include "goldpile.h"
#include "room.h"
#include "tunnel.h"

class Room;

class Tunnel;

class Level {
	public:
		Level(int);
		Terrain& tileAt(Coord);
		Terrain& operator[](Coord);
		void generate(PlayerChar);
		bool contains(Coord);
		static Coord getSize() { return Coord(X_SIZE, Y_SIZE); };

		// Add a mob to the level's collection
		void registerMob(Mob*);

		std::vector<Mob*> getMobs();
		Mob* popTurnClock();

		// move a mob back in the turn clock equal to the amount specified
		void pushMob(Mob*, int);

		//Performs BFS with diagonals
		std::vector<Coord> bfsDiag(Coord, Coord);

		//Performs BFS without diagonals
		std::vector<Coord> bfsPerp(Coord, Coord);

		//Gets a path given a delta vector and starting position
		std::vector<Coord> getPath(std::vector<Coord>, Coord);


		std::vector<Coord> getAdjPassable(Coord);

		Coord throwLocation(Coord, Coord);

	private:

		// Store mobs with a notation for how many
		// 'ticks' they are from being the current actor
		struct ClockItem {
			ClockItem(Mob* mob, int delay) 
				: mob(mob)
				, delay(delay) {}
			Mob* mob;
			int delay;
		};

		const int MAX_ROOMS = 9;
		const double GOLD_CHANCE = .333;
		const double ROOM_EXIST_CHANCE = 0.9;
		static const int ROOM_PADDING = 2;
		static const int MIN_ROOM_DIM = 3;
		static const int X_SIZE = 80, Y_SIZE = 35;//80,25
		std::vector<std::vector<Terrain> > tiles;
		std::vector<Room> rooms;
		std::vector<ClockItem> mobs;
		std::vector<GoldPile> golds;
		std::vector<Tunnel> tunnels;
		int genGoldAmount(Generator);
		void addTunnel(int, int, bool*, bool*, Generator);
		Coord size;
		int depth;

		//Add perpendicular coords
		void addPerps(Coord, std::queue<Coord>&, std::map<Coord, Coord>&);

		//Add diagonal coords
		void addDiags(Coord, std::queue<Coord>&, std::map<Coord, Coord>&);

		//Add diagonal coords
		void tryAdd(Coord, std::queue<Coord>&, std::map<Coord, Coord>&, Coord);
};
