/**
 * @file room.h
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Member declarations for the Room class
 */ 

#pragma once

#include "coord.h"
#include "level.h"

class Level;

/**
 * @brief      Models a room - a rectangular region of which there are (usually) 9 in any given dungeon level. Rooms are connected by tunnels.
 * @see  Tunnel
 */
class Room {
	public:
		enum Darkness {DARK, LIT};
		enum Treasure {TREASURE, WORTHLESS};
		enum Hidden {HIDDEN, VISIBLE};

		Room(Coord, Coord, Darkness, Treasure, Hidden, Coord, bool);
		Room(Coord, Coord);
		Coord operator[](int);

		/**
		 * @brief      Clears a passable room in the designated level
		 *
		 * @param      Level The level in which to dig
		 */
		void dig(Level&);

		Coord getPosition1();
		Coord getPosition2();
		Coord getRoomSize();
		Coord getRoomIndex();

		/**
		 * @brief      A non-existent room is one which is a 1x1 tunnel tile.
		 *
		 * @return     True if the room is real, false if it is simply a tunnel piece.
		 */
		bool exists();

		/**
		 * @brief      Tells you whether or not the coordinate touches the room
		 *
		 * @param[in]  Coord The location to test
		 *
		 * @return     True if coord can touch or intersect with the room, false otherwise
		 */
		bool touches(Coord);

		/**
		 * @brief      A diagnostic tool
		 *
		 * @param[in]  An integer to go along with the info (Used when printing info of multiple rooms).
		 */
		void printInfo(int);

		/**
		 * @brief      Tells you whether or not the coordinate is contained by the room
		 *
		 * @param      Coord The coordinate to test
		 *
		 * @return     True if the input is within the room, false otherwise.
		 */
		bool contains(Coord&, int border=0);

		Darkness getDark();

	private:
		Coord topLeft;
		Coord bottomRight;
		Darkness isDark;
		Treasure isTreasure;
		Hidden isHidden;
		Coord roomIndex;
		bool ex;
};
