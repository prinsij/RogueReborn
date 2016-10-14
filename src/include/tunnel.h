
#pragma once

#include "room.h"
#include "level.h"
#include "random.h"

class Room;

class Level;

class Tunnel {
	public:
		enum Direction {Up, Down, Left, Right, None};
		Tunnel(Room*, Room*, Generator);
		void dig(Level&);
	private:
		Tunnel::Direction flip(Tunnel::Direction);
		Coord getDoorPlacement(Room*, Tunnel::Direction);
		Room* p;
		Room* q;
		Generator gen;
};