#include "include/room.h"
#include "include/coord.h"
#include "include/tiles.h"
#include <stdexcept>
#include <string>
#include <iostream>

Room::Room(Coord topLeft, Coord bottomRight)
	: Room(topLeft, bottomRight, LIT, WORTHLESS, VISIBLE, Coord(0,0), true)
	{}

Room::Room(Coord topLeft, Coord bottomRight, Darkness dark, Treasure treas, Hidden hid, Coord rIndex, bool exist)
	: topLeft(topLeft)
	, bottomRight(bottomRight)
	, isDark(dark)
	, isTreasure(treas)
	, isHidden(hid)
	, roomIndex(rIndex)
	, ex(exist)
{}

Coord Room::operator[](int corner) {
	if (corner == 0) {
		return topLeft;
	} else if (corner == 1) {
		return bottomRight;
	}
	throw std::invalid_argument("param must be 0 or 1, not " + std::to_string(corner));
}

Coord Room::getPosition1(){
	return topLeft;
}

Coord Room::getPosition2(){
	return bottomRight;
}

Coord Room::getRoomSize(){
	return bottomRight - topLeft + Coord(1,1);
}

Coord Room::getRoomIndex(){
	return roomIndex;
}

bool Room::exists(){
	return ex;
}

bool Room::touches(Coord c){

	Coord a = topLeft + Coord(-1, -1);
	Coord b = bottomRight + Coord(1, 1);

	if (a[0] <=  c[0] && c[0] <= b[0]){
		if (a[1] <= c[1] && c[1] <= b[1]){
			return true;
		}
	}

	return false;
}

void Room::printInfo(int numToDisplay){
	std::cout << "ROOM " << numToDisplay  << " (" << roomIndex[0] << ", " << roomIndex[1] << ")" << std::endl;
	std::cout << "Start: " << getPosition1()[0] << ", " << getPosition1()[1]<< std::endl;
	std::cout << "End: " << getPosition2()[0] << ", " << getPosition2()[1]<< std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~" << std::endl << std::endl;
}

void Room::dig(Level& level) {
	for (auto x=topLeft[0]; x <= bottomRight[0]; x++) {
		for (auto y=topLeft[1]; y <= bottomRight[1]; y++) {
			level[Coord(x, y)] = Floor();
		}
	}
}
