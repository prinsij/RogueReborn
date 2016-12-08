/**
 * @file coord.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the Coord class
 */ 

#include <algorithm>
#include <cmath>
#include <string>

#include "include/coord.h"

Coord Coord::ORTHO[4] = {Coord(0,1), Coord(1,0),
						  Coord(0,-1), Coord(-1,0)};

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

Coord Coord::asScreen() {
	return Coord(x + MAPX, y + MAPY);
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

Coord Coord::operator*(const int& scalar) {
	return Coord(this->x * scalar, this->y * scalar);
}

Coord& Coord::operator+=(const Coord& other) {
	*this = *this + other;
	return *this;
}

Coord& Coord::operator-=(const Coord& other) {
	*this = *this - other;
	return *this;
}

bool Coord::operator<(const Coord& other) const {
	return std::sqrt(x * x + y * y) < std::sqrt(other.x * other.x + other.y * other.y);
}

Coord& Coord::operator*=(const int& scalar) {
	*this = *this * scalar;
	return *this;
}

bool Coord::operator==(const Coord& other) {
	return x == other.x && y == other.y;
}

bool Coord::operator!=(const Coord& other) {
	return not (*this == other);
}

std::string Coord::toString() const{
	return std::to_string(x) + ", " + std::to_string(y);
}

int Coord::distanceTo(const Coord& other, bool taxicab) const {
	if (taxicab) {
		return std::abs(x - other.x) + std::abs(y - other.y);
	} else {
		return std::max(std::abs(x - other.x), std::abs(y - other.y));
	}
}


bool Coord::isAdjacentTo(const Coord& other) const {
	return (std::abs(this->x - other.x) + std::abs(this->y - other.y)) <= 1;
}
