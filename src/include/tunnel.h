/**
 * @file tunnel.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Tunnel class
 */ 

#pragma once

#include "level.h"
#include "random.h"
#include "room.h"

class Room;

class Level;

class Tunnel {
	public:
		enum Direction {Up, Down, Left, Right, None};
		Tunnel(Room*, Room*, Generator);
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