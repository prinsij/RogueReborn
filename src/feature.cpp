/**
 * @file feature.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Member definitions for the Feature class
 */ 

#include "include/coord.h"
#include "include/feature.h"

const std::vector<TCODColor> Feature::possibleColors = {TCODColor::lightBlue, TCODColor::red, TCODColor::orange,
							TCODColor::green, TCODColor::purple, TCODColor::yellow};

Feature::Feature(char symbol, Coord location, bool visible, TCODColor fcolor)
	: location(location)
	, symbol(symbol)
	, visible(visible)
	, fcolor(fcolor)
{}

char Feature::getSymbol() {
	return this->symbol;
}

bool Feature::getVisible() {
	return this->visible;
}

void Feature::setVisible(bool newvis) {
	this->visible = newvis;
}

Coord Feature::getLocation() {
	return this->location;
}

void Feature::setLocation(Coord newLoc) {
	this->location = newLoc;
}

TCODColor Feature::getFColor() {
	return this->fcolor;
}

Feature::~Feature() {}
