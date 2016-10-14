#pragma once

#include <vector>
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
		void registerMob(Mob*);
		std::vector<Mob*> getMobs();
		Mob* popTurnClock();
		void pushMob(Mob*, int);
	private:
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
};
