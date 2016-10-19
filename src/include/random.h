#include <random>
#include <string>
#include <vector>

#include "coord.h"

#ifndef RANDOM_H
#define RANDOM_H

class Generator {
	public:
		Generator();
		int intFromRange(int, int);
		double operator()();
		Coord randPosition(Coord, Coord);
		void shuffle(std::vector<Coord>*);
	private:
		std::mt19937 gen;
};

#endif
