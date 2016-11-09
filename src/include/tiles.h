/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: tiles.h
 */ 

#pragma once

#include "terrain.h"

/** Regular dungeon floor. 
 * Has full visibility and passability.
 */
class Floor : public Terrain {
	public:
		Floor();
};

/** Regular dungeon wall.
 * Has no visiblity or passability.
 */
class Wall : public Terrain {
	public:
		Wall();
};

/** Regular corridor tile.
 * Has limited visibility and full passability
 */
class Corridor : public Terrain {
	public:
		Corridor();
};

/** Door tile.
 * Only cosmetically different from corridor tile.
 * @see Corridor
 */
class Door : public Terrain {
	public:
		Door();
};
