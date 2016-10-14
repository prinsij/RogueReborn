#pragma once

#include "coord.h"

class Feature {
	public:
		Feature(char, Coord);
		char getSymbol();
		Coord getLocation();
	private:
		Coord location;
		char symbol;
};
