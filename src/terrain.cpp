#include "include/terrain.h"

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass)
	: character(character)
	, visible(vis)
	, passable(pass)
{}

Terrain::Passability Terrain::isPassable() {
	return passable;
}

char Terrain::getChar() {
	return character;
}

Terrain::Visibility Terrain::getVisibility() {
	return visible;
}

Terrain::Passability Terrain::isPassable() {
	return passable;
}