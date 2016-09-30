#include "coord.h"
#include "level.h"

class Room {
	public:
		Room(Coord, Coord);
		Coord operator[](int);
		void dig(Level&);
		Coord getPosition1();
		Coord getPosition2();
	private:
		Coord topLeft;
		Coord bottomRight;
};
