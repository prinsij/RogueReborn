#pragma once

#include "coord.h"
#include "item.h"

class Amulet : public Item {
	public:
		Amulet(Coord, Item::Context);
};