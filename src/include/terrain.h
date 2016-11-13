

#ifndef TERRAIN_H
#define TERRAIN_H

class Terrain {
	public:
		enum Passability {P_Blocked, Passable};
		enum Visibility {V_Blocked, Corridor, Transparent};
		Terrain(char, Visibility, Passability);
		char getChar();
		Passability isPassable();
		Visibility getVisibility();
	private:
		char character;
		Visibility visible;
		Passability passable;
};

#endif
