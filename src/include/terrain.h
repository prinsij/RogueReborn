
#include "coord.h"

#ifndef TERRAIN_H
#define TERRAIN_H

class Coord;

class Terrain {
	public:
		enum Passability {Blocked, Passable};
		enum Visibility {Opaque, Corridor, Transparent};
		enum Mapped {Seen, UnSeen};
		Terrain(char, Visibility, Passability); 
		char getSymbol();
		Passability isPassable();
		Mapped isSeen();
		Visibility getVisibility();
<<<<<<< HEAD
		bool checked = false;
		Coord parent;
=======
		void setIsSeen(Mapped);
>>>>>>> 4e011a31a79d32522ad4c3345d5db97c6746eafd
	private:
		char character;
		Visibility visible;
		Passability passable;
		Mapped seen;
};

#endif
