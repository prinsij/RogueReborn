

#ifndef TERRAIN_H
#define TERRAIN_H

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
		void setIsSeen(Mapped);
	private:
		char character;
		Visibility visible;
		Passability passable;
		Mapped seen;
};

#endif
