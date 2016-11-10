/**
 * @file level.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Level class
 */ 

#pragma once

#include <map>
#include <queue>
#include <vector>

#include "coord.h"
#include "feature.h"
#include "goldpile.h"
#include "playerchar.h"
#include "random.h"
#include "room.h"
#include "terrain.h"
#include "tunnel.h"

class Room;

class Tunnel;

class Level {
	public:
		Level(int);
		Terrain& tileAt(Coord);
		Terrain& operator[](Coord);
		void generate(PlayerChar&);
		bool contains(Coord);
		int getDepth();
		static Coord getSize() { return Coord(X_SIZE, Y_SIZE); };

		/**
		 * @brief      Adds a mob to the mobs known by the level
		 *
		 * @param      Mob* Pointer to the mob that is to be added
		 */
		void registerMob(Mob*);

		/**
		 * @brief      Removes a mob.
		 *
		 * @param      Mob* Pointer to the mob that is to be removed
		 */
		void removeMob(Mob*);

		/**
		 * @brief      Gets all the mobs on the level
		 *
		 * @return     The mobs.
		 */
		std::vector<Mob*> getMobs();

		/**
		 * @brief      Returns the mob who's turn to act is next
		 *
		 * @return     A mob
		 */
		Mob* popTurnClock();

		// move a mob back in the turn clock equal to the amount specified
		

		/**
		 * @brief      Moves a mob back in the turn clock equal to the amount specified
		 *
		 * @param      Mob* Which mob
		 * @param      int How far to push back in the clock cycle
		 */
		void pushMob(Mob*, int);

		/**
		 * @brief      Performs BFS to get the shortest path from the starting coordinate to the end coordinate. As opposed to bfsPerp, this algorithm is allowed to move in any of the 8 directions.
		 *
		 * @param[in]  Coord  Starting point
		 * @param[in]  Coord  Ending point
		 *
		 * @return     A vector of the absolute coordinates of the shortest path, including start and end, starting at the start and moving forwards one unit vector at a time.
		 * @see bfsPerp
		 */
		std::vector<Coord> bfsDiag(Coord, Coord);

		//Performs BFS without diagonals, returns deltas

		/**
		 * @brief      Performs BFS to get the shortest path from the starting coordinate to the end coordinate. As opposed to bfsDiag, this algorithm is allowed to move only in the 4 cardinal direcitons.
		 *
		 * @param[in]  Coord  Starting point
		 * @param[in]  Coord  Ending point
		 *
		 * @return     A vector of the absolute coordinates of the shortest path, including start and end, starting at the start and moving forwards one unit vector at a time.
		 * @see bfsDiag
		 */
		std::vector<Coord> bfsPerp(Coord, Coord);

		//Given a coord, returns coords to which you can move to nearby (3x3 box)
		std::vector<Coord> getAdjPassable(Coord);

		//Given a start and a delta direction, returns a coord of where something thrown would land
		Coord throwLocation(Coord, Coord);

		std::vector<Room>& getRooms();

		std::vector<Feature*>& getFeatures();

		void removeFeature(Feature*);

		void addFeature(Feature*);

		Mob* monsterAt(Coord);

		~Level();

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
#define MAX_ROOMS_DEF (9)
		static const int MAX_ROOMS = 9;
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
};