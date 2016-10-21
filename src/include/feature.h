#pragma once

#include "coord.h"

class Feature {
	public:
		Feature(char, Coord);
		char getSymbol();
		Coord getLocation();
		virtual ~Feature();
	private:
		Coord location;
		char symbol;
};
