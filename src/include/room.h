#pragma once

#include "coord.h"
#include "level.h"

class Level;

class Room {
	public:
		enum Darkness {DARK, LIT};
		enum Treasure {TREASURE, WORTHLESS};
		enum Hidden {HIDDEN, VISIBLE};
		Room(Coord, Coord, Darkness, Treasure, Hidden, Coord);
		Room(Coord, Coord);
		Coord operator[](int);
		void dig(Level&);
		Coord getPosition1();
		Coord getPosition2();
		bool exists();
		void printInfo(int);
	private:
		Coord topLeft;
		Coord bottomRight;
		Darkness isDark;
		Treasure isTreasure;
		Hidden isHidden;
		Coord roomIndex;

};
