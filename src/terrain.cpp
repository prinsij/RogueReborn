/**
 * @file terrain.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member definitions for the Terrain class
 */ 

#include "include/terrain.h"

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass)
	: character(character)
	, visible(vis)
	, passable(pass)
	, seen(UnSeen)
	, color(TCODColor::white)
{}

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass, TCODColor col)
	: character(character)
	, visible(vis)
	, passable(pass)
	, seen(UnSeen)
	, color(col)
{}

char Terrain::getSymbol() {
	return character;
}

void Terrain::setSymbol(char newSymbol) {
	this->character = newSymbol;
}

TCODColor Terrain::getColor() {
	return color;
}

Terrain::Visibility Terrain::getVisibility() {
	return visible;
}

Terrain::Passability Terrain::isPassable() {
	return passable;
}

Terrain::Mapped Terrain::isSeen() {
	return seen;
}

void Terrain::setIsSeen(Terrain::Mapped newState) {
	seen = newState;
}

void Terrain::setPassable(Passability pass) {
	this->passable = pass;
}

Terrain::~Terrain() {};
