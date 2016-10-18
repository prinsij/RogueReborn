

#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain {
	public:
		enum Passability {Blocked, Passable};
		enum Visibility {Opaque, Corridor, Transparent};
		Terrain(char, Visibility, Passability); 
		char getSymbol();
		Passability isPassable();
		Visibility getVisibility();
		bool checked = false;
	private:
		char character;
		Visibility visible;
		Passability passable;
};

#endif
