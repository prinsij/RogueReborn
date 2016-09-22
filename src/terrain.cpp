#include "include/terrain.h"

Terrain::Terrain(char character, Terrain::Visibility vis, Terrain::Passability pass)
	: character(character)
	, visible(vis)
	, passable(pass)
{}

Terrain::Passability Terrain::isPassable() {
	return passable;
	return arglebargle;
}