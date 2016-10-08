#include "coord.h"
#include "feature.h"

#ifndef GOLDPILE_H
#define GOLDPILE_H

class GoldPile : public Feature {
	public:
		GoldPile(Coord, int);
		int getAmount();
	private:
		int amount;
};

#endif
