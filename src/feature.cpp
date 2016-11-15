/**
 * @file feature.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Feature class
 */ 

#include "include/coord.h"
#include "include/feature.h"

Feature::Feature(char symbol, Coord location, bool visible)
	: location(location)
	, symbol(symbol) 
	, visible(visible)
{}

char Feature::getSymbol() {
	return this->symbol;
}

bool Feature::getVisible() {
	return this->visible;
}

Coord Feature::getLocation() {
	return this->location;
}

void Feature::setLocation(Coord newLoc) {
	this->location = newLoc;
}

Feature::~Feature() {}
