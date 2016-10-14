
#include "include/tunnel.h"
#include "include/terrain.h"
#include <vector>
#include <iostream>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"

Tunnel::Tunnel(Room* p, Room* q) 
	: p(p)
	, q(q)
{}

void Tunnel::dig(Level& level){

	//1. Place doors
	//2. Pathfind from A to B
	//3. Occasionally make random move

	Coord pi = p->getRoomIndex();
	Coord qi = q->getRoomIndex();

	//Directions relative to P

	//Left
	if (p[0] < q[0]){

	}

	//Right
	else if (p[0] > q[0]){

	}

	//Up
	else if (p[1] < q[1]){

	}

	//Down
	else if (p[1] > q[1]){

	}

	else {
		std::cout << "There has been a VERY SERIOUS ERROR" << std::endl;
	}
}