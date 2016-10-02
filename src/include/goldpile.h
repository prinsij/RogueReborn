#include "coord.h"

#ifndef GOLDPILE_H
#define GOLDPILE_H

class GoldPile {
	public:
		GoldPile(Coord, int);
		Coord getPosition();
		int getAmount();
	private:
		Coord position;
		int amount;
};

#endif
