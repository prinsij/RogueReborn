
#pragma once

#include "room.h"
#include "level.h"

class Room;

class Level;

class Tunnel {
	public:
		Tunnel(Room*, Room*);
		void dig(Level&);
	private:
		Room* p;
		Room* q;
};