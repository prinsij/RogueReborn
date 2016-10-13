#include "include/room.h"
#include "include/coord.h"
#include "include/tiles.h"
#include <stdexcept>
#include <string>

Room::Room(Coord topLeft, Coord bottomRight)
	: Room(topLeft, bottomRight, LIT, WORTHLESS, VISIBLE, EXISTS)
	{}

Room::Room(Coord topLeft, Coord bottomRight, Darkness dark, Treasure treas, Hidden hid, Existence ext)
	: topLeft(topLeft)
	, bottomRight(bottomRight)
	, isDark(dark)
	, isTreasure(treas)
	, isHidden(hid)
	, isExisting(ext)
{}

Coord Room::operator[](int corner) {
	if (corner == 0) {
		return topLeft;
	} else if (corner == 1) {
		return bottomRight;
	}
	throw std::invalid_argument("param must be 0 or 1, not " + std::to_string(corner));
}


void Room::dig(Level& level) {
	for (auto x=topLeft[0]; x <= bottomRight[0]; x++) {
		for (auto y=topLeft[1]; y <= bottomRight[1]; y++) {
			level[Coord(x, y)] = Floor();
		}
	}
}

bool Room::exists(){
	return isExisting == Room::EXISTS;
}
