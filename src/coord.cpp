#include "include/coord.h"
#include <string>

Coord::Coord(int x, int y)
	: x(x)
	, y(y)
	{}

int& Coord::operator[](int dimension) {
	switch (dimension) {
		case 0:
			return this->x;
		case 1:
			return this->y;
	}
	throw "bad dimension " + std::to_string(dimension);
	return this->x;
}

Coord Coord::operator+(const Coord& other) {
	return Coord(this->x + other.x, this->y + other.y);
}

Coord Coord::operator-(const Coord& other) {
	return Coord(this->x - other.x, this->y - other.y);
}
