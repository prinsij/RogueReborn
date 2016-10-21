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
#include "feature.h"

class Room;

class Tunnel;

class Level {
	public:
		Level(int);
		Terrain& tileAt(Coord);
		Terrain& operator[](Coord);
		void generate(PlayerChar);
		bool contains(Coord);
		int getDepth();
		static Coord getSize() { return Coord(X_SIZE, Y_SIZE); };

		// Add a mob to the level's collection
		void registerMob(Mob*);

		std::vector<Mob*> getMobs();
		Mob* popTurnClock();

		// move a mob back in the turn clock equal to the amount specified
		void pushMob(Mob*, int);

		//Performs BFS with diagonals, returns deltas
		std::vector<Coord> bfsDiag(Coord, Coord);

		//Performs BFS without diagonals, returns deltas
		std::vector<Coord> bfsPerp(Coord, Coord);

		//Given a coord, returns coords to which you can move to nearby (3x3 box)
		std::vector<Coord> getAdjPassable(Coord);

		//Given a start and a delta direction, returns a coord of where something thrown would land
		Coord throwLocation(Coord, Coord);

		std::vector<Room>& getRooms();

		std::vector<Feature*>& getFeatures();

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

		const Coord nearby[8] = { Coord(-1,-1), Coord(0,-1), Coord(1,-1), Coord(1,0), Coord(1,1), Coord(0,1), Coord(-1,1), Coord(-1,0) };
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
		std::vector<Feature*> features;
		int genGoldAmount(Generator);
		void addTunnel(int, int, bool*, bool*, Generator);
		Coord size;
		int depth;

		//Try to add a coord to the q
		void tryAddPassable(Coord, std::queue<Coord>&, Coord);

		//Try to add a coord to the q
		void tryAdd(Coord, std::queue<Coord>&, Coord);

		void resetPF();

		std::vector<Coord> traceBack(Coord, Coord);
		bool monsterAt(Coord);
};
