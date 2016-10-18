

#pragma once

#include "include/terrain.h"
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include <map>
#include <vector>

class Level;

class Algs {
	public:

		Algs();

		//Performs BFS with diagonals
		std::vector<Coord> bfsDiag(Coord, Coord);

		//Performs BFS without diagonals
		std::vector<Coord> bfsPerp(Coord, Coord);

		//Gets a path given a delta vector and starting position
		std::vector<Coord> getPath(Coord, std::vector<Coord>);

	private:

		//Add perpendicular coords
		void addPerps(Coord, std::vector<Coord>, Level* , std::map<Coord, Coord>);

		//Add diagonal coords
		void addDiags(Coord, std::vector<Coord>, Level* , std::map<Coord, Coord>);

		//Add diagonal coords
		void tryAdd(Coord, std::vector<Coord>, Level* , std::map<Coord, Coord>, Coord);
};