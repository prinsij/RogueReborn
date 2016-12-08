/**
 * @file level.h
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member declarations for the Level class
 */ 

#pragma once

#include <map>
#include <queue>
#include <tuple>
#include <vector>

#include "coord.h"
#include "feature.h"
#include "goldpile.h"
#include "playerchar.h"
#include "random.h"
#include "room.h"
#include "terrain.h"
#include "trap.h"
#include "tunnel.h"

class Room;

class Tunnel;

class Level {
	public:
		Level(int, PlayerChar*);
		Terrain& tileAt(Coord);
		Terrain& operator[](Coord);
		void generate();
		bool contains(Coord);
		int getDepth();
		PlayerChar* getPlayer();
		static Coord getSize() { return Coord(X_SIZE, Y_SIZE); };

		void clear();

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
		std::tuple<Mob*, int> popTurnClock();

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
		 * @param Coord  Starting point
		 * @param Coord  Ending point
		 *
		 * @return     A vector of the absolute coordinates of the shortest path, including start and end, starting at the start and moving forwards one unit vector at a time.
		 * @see bfsPerp
		 */
		std::vector<Coord> bfsDiag(Coord, Coord);

		//Performs BFS without diagonals, returns deltas

		/**
		 * @brief      Performs BFS to get the shortest path from the starting coordinate to the end coordinate. As opposed to bfsDiag, this algorithm is allowed to move only in the 4 cardinal direcitons.
		 *
		 * @param Coord  Starting point
		 * @param Coord  Ending point
		 *
		 * @return     A vector of the absolute coordinates of the shortest path, including start and end, starting at the start and moving forwards one unit vector at a time.
		 * @see bfsDiag
		 */
		std::vector<Coord> bfsPerp(Coord, Coord);

		//Given a coord, returns coords to which you can move to nearby (3x3 box)

		/**
		 * @brief      Gets the coordinates to which one can move to from a given source (3x3 box)
		 *
		 * @param  Coord  Coordinate to check from
		 * @param  noMonster True if tiles with Monsters should be excluded
		 *
		 * @return     A vector of coordinates onto which you can move.
		 */
		std::vector<Coord> getAdjPassable(Coord, bool);

		//Given a start and a delta direction, returns a coord of where something thrown would land

		/**
		 * @brief      Given a start and a delta direction, returns the position of where something thrown would land
		 *
		 * @param Coord Where the object is being thrown from
		 * @param Coord The direction in which it is being thrown (Must be a unit vector!)
		 *
		 * @return     Final location
		 */
		Coord throwLocation(Coord, Coord);

		/**
		 * @brief      Gets the rooms.
		 *
		 * @return     The rooms.
		 */
		std::vector<Room>& getRooms();

		/**
		 * @brief      Gets the features.
		 *
		 * @return     The features.
		 */
		std::vector<Feature*>& getFeatures();

		/**
		 * @brief      Removes a feature.
		 *
		 * @param      Feature The feature to remove
		 */
		void removeFeature(Feature*);

		/**
		 * @brief      Adds a feature.
		 *
		 * @param      Feature The feature to add
		 */
		void addFeature(Feature*);

		/**
		 * @brief      Returns the monster that is at the location
		 *
		 * @param[in]  Coord The location to get the monster from
		 *
		 * @return     Returns the pointer to a monster if there is one at the specified location, NULL otherwise.
		 */
		Mob* monsterAt(Coord);

		/**
		 * @brief      Determines ability to see each other
		 *
		 * @param[in]  Coord A
		 * @param[in]  Coord B
		 *
		 * @return     True if able to see, False otherwise.
		 */
		bool canSee(Coord, Coord);

		/**
		 * @brief      Gets the path to the nearest gold.
		 *
		 * @param[in]  Coord Origin to search from
		 *
		 * @return     The path to the nearest gold. NULL if there is no gold to find.
		 */
		std::vector<Coord> getNearestGold(Coord);

		/**
		 * @brief	Place the player at a random empty position.
		 */
		void placePlayerInStartingPosition();

		/**
		 * @brief	Return a random coord within the level,
		 *			with no mobs.
		 *
		 * @return	A random coord within the level,
		 *			with no mobs.
		 */
		Coord getRandomEmptyPosition();

		/**
		 * @brief	Places a depth-appropriate monster
		 *			somewhere in the level.
		 */
		void putRandomMonster();

		~Level();

	private:

		PlayerChar* player;

		/**
		 * @brief      Store mobs with a notation for how many 'ticks' they are from being the current actor
		 */
		struct ClockItem {
			ClockItem(Mob* mob, int delay)
				: mob(mob)
				, delay(delay) {}
			Mob* mob;
			int delay;
		};

		/**
		 * A list of delta-vectors that reach adjacent locations in a 3x3 box
		 */
		const Coord nearby[8] = { Coord(-1,-1), Coord(0,-1), Coord(1,-1), Coord(1,0), Coord(1,1), Coord(0,1), Coord(-1,1), Coord(-1,0) };

		//Indentation is weird here
#define MAX_ROOMS_DEF (9)

		/**
		 * The maximum number of room in a level
		 */
		static const int MAX_ROOMS = 9;

		/**
		 * The chance of generating gold
		 */
		static constexpr double GOLD_CHANCE = .333;

		/**
		 * The chance of a room being an actual room instead of just a passageway
		 */
		static constexpr double ROOM_EXIST_CHANCE = 0.9;

		/**
		 * Minimum number of tiles padding each room (essentially half of the minimum number of tiles between rooms)
		 */
		static const int ROOM_PADDING = 2;

		/**
		 * Minimum dimension (both x and y) of each room
		 */
		static const int MIN_ROOM_DIM = 3;

		/**
		 * Size of the level
		 */
		static const int X_SIZE = 80, Y_SIZE = 35;

		/**
		 * The tiles of the level
		 */
		std::vector<std::vector<Terrain> > tiles;

		/**
		 * The rooms of the level
		 */
		std::vector<Room> rooms;

		/**
		 * The mobs in the level
		 */
		std::vector<ClockItem> mobs;

		/**
		 * The gold piles in the level
		 */
		std::vector<GoldPile> golds;

		/**
		 * The tunnels in the level (connecting rooms)
		 */
		std::vector<Tunnel> tunnels;

		/**
		 * The features in the level (i.e. items, stairs, traps, etc.)
		 */
		std::vector<Feature*> features;

		int genGoldAmount();

		/**
		 * @brief      Adds a tunnel.
		 *
		 * @param  int			Room index to go FROM
		 * @param  int			Room index to go TO
		 * @param  bool*		Maintainer of tunnel transitivity property for A
		 * @param  bool*		Maintainer of tunnel transitivity property for B
		 * @param  Generator	A generator to pass around (Might not need this anymore)
		 */
		void addTunnel(int, int, bool*, bool*);
		Coord size;
		int depth;

		//Try to add a coord to the q
		void tryAddPassable(Coord, std::queue<Coord>&, Coord, Coord);

		//Try to add a coord to the q
		void tryAdd(Coord, std::queue<Coord>&, Coord);

		void resetPF();

		std::vector<Coord> traceBack(Coord, Coord);

		static constexpr int THINGS_PER_KIND = 3;
};
