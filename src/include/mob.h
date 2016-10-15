#pragma once

#include <string>

#include "coord.h"

class Mob {
	public:
		Mob(std::string, char, Coord, int, int, int, int);
		
		static int diceSum(int, int);

		virtual void attack(Mob*) = 0;
		void changeArmor(int);
		int getArmor();
		int getExperience();
		int getHP();
		int getLevel();
		Coord& getLocation();
		std::string getName();
		char getSymbol();
		void moveLocation(Coord);
		void setCurrentHP(int);
		void setLocation(Coord);
		void setMaxHP(int);

		~Mob();

	private:
		int armor;
		int currentHP;
		int exp;
		int level;
		Coord location;
		int maxHP;
		std::string name;
		char symbol;
};
