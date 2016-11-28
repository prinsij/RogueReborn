/**
 * @file tunnel.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the Tunnel class
 */ 

#pragma once

#include "level.h"
#include "random.h"
#include "room.h"

class Room;

class Level;

/**
 * @brief      Tunnels are step-orthogonal paths connecting rooms
 */
class Tunnel {
	public:

		/**
		 * @brief      An enum to represent step directions
		 */
		enum Direction {Up, Down, Left, Right, None};

		/**
		 * @brief      Creates a tunnel between the two rooms
		 *
		 * @param      Room*  The room to go FROM
		 * @param      Room*  The room to go TO
		 * @param      Generator  The random generator to use
		 */
		Tunnel(Room*, Room*, Generator);

		/**
		 * @brief      Digs the specified tunnel in the given level
		 *
		 * @param      Level&  The level in which to dig this tunnel
		 */
		void dig(Level&);
	private:
		const double TUNNEL_CONFUSION = 0.1;
		Tunnel::Direction flip(Tunnel::Direction);
		Coord getDoorPlacement(Room*, Tunnel::Direction);
		Coord findNextStep(Coord, std::vector<std::vector<double> >);
		Coord posPlusDir(Coord, Tunnel::Direction);
		Room* p;
		Room* q;
		Generator gen;
};
