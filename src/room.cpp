#include "include/room.h"
#include "include/coord.h"
#include <stdexcept>
#include <string>

Room::Room(Coord topLeft, Coord bottomRight)
	: topLeft(topLeft)
	, bottomRight(bottomRight)
	{}

Coord Room::operator[](int corner) {
	if (corner == 0) {
		return topLeft;
	} else if (corner == 1) {
		return bottomRight;
	}
	throw std::invalid_argument("param must be 0 or 1, not " + std::to_string(corner));
}
