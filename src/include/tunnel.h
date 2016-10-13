
#pragma once

#include "room.h"

class Room;

class Tunnel {
	public:
		Tunnel(Room*, Room*);
		Room* p;
		Room* q;
};