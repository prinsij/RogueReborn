/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: feature.cpp
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