#pragma once

#include "coord.h"

class Feature {
	public:
		Coord getCoord();
		Feature(char, Coord);
		char getChar();
	private:
		char symbol;
		Coord coord;
};
