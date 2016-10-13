#include "coord.h"
#include <string>

#ifndef MOB_H
#define MOB_H

class Mob {
	public:
		Mob(std::string, char, Coord, int);
		char getChar();
		int getHP();
		void setHP();
		int getMaxHP();
		Coord& getCoord();
		void setCoord(Coord);
		int& operator[](int);
		std::string getName();
	private:
		std::string name;
		char symbol;
		Coord coord;
		int HP, maxHP;
};

#endif
