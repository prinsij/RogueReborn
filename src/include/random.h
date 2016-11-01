#pragma once

#include <random>
#include <string>
#include <vector>

#include "coord.h"

class Generator {
	public:
		static int intFromRange(int, int);
		static double rand();
		static bool randBool();
		static Coord randPosition(Coord, Coord);
		static void shuffle(std::vector<Coord>*);
	private:
		static std::mt19937 gen;
};
