/**
 * @file feature.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Feature class
 */ 

#include "include/coord.h"
#include "include/feature.h"

Feature::Feature(char symbol, Coord location)
	: location(location),
	  symbol(symbol) {}

char Feature::getSymbol() {
	return this->symbol;
}

Coord Feature::getLocation() {
	return this->location;
}

void Feature::setLocation(Coord newLoc) {
	this->location = newLoc;
}

Feature::~Feature() {}