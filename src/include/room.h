#pragma once

#include "coord.h"
#include "level.h"

class Level;

class Room {
	public:
		enum Darkness {DARK, LIT};
		enum Treasure {TREASURE, WORTHLESS};
		enum Hidden {HIDDEN, VISIBLE};
		Room(Coord, Coord, Darkness, Treasure, Hidden, Coord, bool);
		Room(Coord, Coord);
		Coord operator[](int);
		void dig(Level&);
		Coord getPosition1();
		Coord getPosition2();
		Coord getRoomSize();
		Coord getRoomIndex();
		bool exists();
		bool touches(Coord);
		void printInfo(int);
		bool contains(Coord&, int border=0);
	private:
		Coord topLeft;
		Coord bottomRight;
		Darkness isDark;
		Treasure isTreasure;
		Hidden isHidden;
		Coord roomIndex;
		bool ex;
};
