
#include "include/tunnel.h"
#include "include/terrain.h"
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdio.h>

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

	Coord target = posPlusDir(qDoor, dir);
	Coord nextPos = posPlusDir(pDoor, flip(dir));
	Coord current = nextPos.copy();
	std::vector<Coord> path;

	std::vector<std::vector<double>> map;
	for (auto x=0; x < level.getSize()[0]; x++) {
		map.push_back(std::vector<double>());
		for (auto y=0; y < level.getSize()[1]; y++) {
			map[x].push_back(sqrt(
				(target[0] - x)*(target[0] - x)+
				(target[1] - y)*(target[1] - y)
				));
		}
	}

	int counter = 0;

	do {

		current = nextPos.copy();

		level[current] = Floor();

		Coord delta = findNextStep(current, map);
		path.push_back(delta);
		nextPos = nextPos + delta;

		counter++;

	} while (current != target || counter > 5000);

}

Coord Tunnel::findNextStep(Coord currPos, std::vector<std::vector<double>> map){

	double currentScore = map[currPos[0]][currPos[1]];
	Coord delta = Coord(0,0);

	if (map[currPos[0]+1][currPos[1]] < currentScore){
		currentScore = map[currPos[0]+1][currPos[1]];
		delta = Coord(1,0);
	}

	if (map[currPos[0]-1][currPos[1]] < currentScore){
		currentScore = map[currPos[0]-1][currPos[1]];
		delta = Coord(-1,0);
	}

	if (map[currPos[0]][currPos[1]-1] < currentScore){
		currentScore = map[currPos[0]][currPos[1]-1];
		delta = Coord(0,-1);
	}

	if (map[currPos[0]][currPos[1]+1] < currentScore){
		currentScore = map[currPos[0]][currPos[1]+1];
		delta = Coord(0,+1);
	}

	return delta;

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

Coord Tunnel::posPlusDir(Coord c, Tunnel::Direction dir){

	switch(dir){
		case Left: return c + Coord(-1, 0);
		case Right: return c + Coord(1, 0);
		case Up: return c + Coord(0, -1);
		case Down: return c + Coord(0, 1);
		default: return c;
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