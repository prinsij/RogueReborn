#include "include/coord.h"
#include "include/feature.h"

Feature::Feature(char symbol, Coord coord)
	: symbol(symbol)
	, coord(coord)
{}

char Feature::getChar() {
	return symbol;
}

Coord Feature::getCoord() {
	return coord;
}
