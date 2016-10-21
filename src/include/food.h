#pragma once

#include <string>

#include "coord.h"
#include "item.h"

class PlayerChar;

class Food : public Item {
	public:
		Food(Coord, Item::Context);
		bool activate(PlayerChar*);
};
