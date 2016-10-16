#pragma once

#include <string>

#include "coord.h"
#include "feature.h"

class Mob;

class Trap : public Feature {
	public:
		Trap(Coord, unsigned char, bool);
		void activate(Mob*);
	private:
		/* 0 = Door Trap
		   1 = Arrow Trap
		   2 = Sleep Trap
		   3 = Bear Trap
		   4 = Teleport Trap
		   5 = Dart Trap
		*/
		unsigned char type;
		bool visible;
};