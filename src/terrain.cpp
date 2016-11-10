/**
 * @file terrain.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Terrain class
 */ 

#include "include/terrain.h"

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass)
	: character(character)
	, visible(vis)
	, passable(pass)
	, seen(UnSeen)
{}

char Terrain::getSymbol() {
	return character;
}

Terrain::Passability Terrain::isPassable() {
	return passable;
}

Terrain::Visibility Terrain::getVisibility() {
	return visible;
}

Terrain::Mapped Terrain::isSeen() {
	return seen;
}

void Terrain::setIsSeen(Terrain::Mapped newState) {
	seen = newState;
}