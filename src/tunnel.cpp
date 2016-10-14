
#include "include/tunnel.h"
#include "include/terrain.h"
#include <vector>
#include <iostream>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"

Tunnel::Tunnel(Room* p, Room* q, Generator gen) 
	: p(p)
	, q(q)
	, gen(gen)
{}

void Tunnel::dig(Level& level){

	//1. Place doors
	//2. Pathfind from A to B
	//3. Occasionally make random move

	Coord pi = p->getRoomIndex();
	Coord qi = q->getRoomIndex();

	//Directions relative to P
	Tunnel::Direction dir = Tunnel::None;

	//Left
	if (pi[0] < qi[0]){
		dir = Tunnel::Left;
	}

	//Right
	else if (pi[0] > qi[0]){
		dir = Tunnel::Right;
	}

	//Up
	else if (pi[1] < qi[1]){
		dir = Tunnel::Up;
	}

	//Down
	else if (pi[1] > qi[1]){
		dir = Tunnel::Down;
	}


	//P's door always goes on the DIR side
	//Q's doors always goes on the opposite side of DIR

	Coord pDoor = getDoorPlacement(p, flip(dir));
	Coord qDoor = getDoorPlacement(q, dir);

	level[pDoor] = Door();
	level[qDoor] = Door();

}

Tunnel::Direction Tunnel::flip(Tunnel::Direction dir){

	switch(dir){
		case Left: return Right;
		case Right: return Left;
		case Up: return Down;
		case Down: return Up;
		default: return None;
	}
}

Coord Tunnel::getDoorPlacement(Room* r, Tunnel::Direction dir){

	switch(dir){
		case Tunnel::Left:
			return gen.randPosition(r->getPosition1()+Coord(-1,0),
									r->getPosition1()+Coord(-1, r->getRoomSize()[1]-1));
			break;

		case Tunnel::Right:
			return gen.randPosition(r->getPosition1()+Coord(r->getRoomSize()[0], 0),
									r->getPosition2()+Coord(1,0));
			break;

		case Tunnel::Up:
			return gen.randPosition(r->getPosition1()+Coord(0,-1),
									r->getPosition1()+Coord(r->getRoomSize()[0]-1, -1));
			break;

		case Tunnel::Down:
			return gen.randPosition(r->getPosition1()+Coord(0, r->getRoomSize()[1]),
									r->getPosition2()+Coord(0, 1));
			break;

		default:
			std::cout << "There has been a VERY SERIOUS ERROR" << std::endl;
			return Coord(0,0);
			break;
	}
}