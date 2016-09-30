#include "coord.h"

#ifndef GOLDPILE_H
#define GOLDPILE_H

class GoldPile {
	public:
		Gold(Coord, int);
		Coord getPosition();
		int getAmount();
	private:
		Coord position;
		int amount;
};

#endif
