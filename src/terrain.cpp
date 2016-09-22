#include "include/terrain.h"

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass)
	: character(character)
	, visible(vis)
	, passable(pass)
{}

char Terrain::getChar() {
	return character;
}

Terrain::Passability Terrain::isPassable() {
	return passable;
}

Terrain::Visibility Terrain::getVisibility() {
	return visible;
}
