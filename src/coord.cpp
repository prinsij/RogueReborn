#include "include/coord.h"
#include <string>

Coord::Coord(int x, int y)
	: x(x)
	, y(y)
	{}

Coord::Coord()
	: x(0)
	, y(0)
	{}

Coord Coord::copy() {
	return Coord(x, y);
}

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

Coord Coord::operator+=(const Coord& other) {
	return *this + other;
}

Coord Coord::operator-=(const Coord& other) {
	return *this - other;
}
