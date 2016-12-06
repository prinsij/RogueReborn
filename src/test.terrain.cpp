/**
 * @file test.terrain.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/terrain.h"
#include "include/tiles.h"
#include "test.testable.h"

class TerrainTest : public Testable {
	public:
		TerrainTest(){}

		//visible
		//passable
		//color
		//char

		void test(){

			comment("Commencing Terrain tests");

			Floor floor = Floor();
			assert(floor.isPassable() == Terrain::Passable, "Floors are passable");
			assert(floor.getSymbol() == '.', "Floors are dots");
			assert(floor.getVisibility() == Terrain::Transparent, "Floors are transparent");

			Wall wall = Wall();
			assert(wall.isPassable() == Terrain::Blocked, "Walls are blocked");
			assert(wall.getSymbol() == '#', "Walls are hashtags");
			assert(wall.getVisibility() == Terrain::Opaque, "Walls are opaque");

			Corridor corridor = Corridor();
			assert(corridor.isPassable() == Terrain::Passable, "Corridors are passable");
			assert(corridor.getSymbol() == '~', "Corridors are squigles");
			assert(corridor.getVisibility() == Terrain::Corridor, "Corridors are of the special corridor visibility level");

			Door door = Door();
			assert(door.isPassable() == Terrain::Blocked, "Doors are blocked");
			assert(door.getSymbol() == '+', "Doors are plus signs");
			assert(door.getVisibility() == Terrain::Corridor, "Doors are are of the special corridor visibility level");

			comment("Finished Terrain tests");
		}
};
