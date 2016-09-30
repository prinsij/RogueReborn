#include "coord.h"
#include "level.h"

class Room {
	public:
		Room(Coord, Coord);
		Coord operator[](int);
		Coord getPosition1();
		Coord getPosition2();
		void dig(Level);
	private:
		Coord topLeft;
		Coord bottomRight;
};
