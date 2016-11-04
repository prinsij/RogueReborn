/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: mob.h
 */ 

#pragma once

#include <string>

#include "coord.h"

class Level;

class Mob {
	public:
		Mob(char, Coord);
		Mob(char, Coord, std::string, int, int, int, int);

		static int diceSum(int, int);

		//virtual void attack(Mob*) = 0;
		virtual int calculateDamage() = 0;
		void changeArmor(int);
		int getArmor();
		int getExperience();
		int getHP();
		int getMaxHP();
		int getLevel();
		Coord& getLocation();
		std::string getName();
		char getSymbol();
		void hit(int);
		void moveLocation(Coord);
		bool setCurrentHP(int);
		void setLocation(Coord);
		void setMaxHP(int);
		virtual int turn(Level*);

		virtual ~Mob();

	protected:
		int armor;
		int currentHP;
		int exp;
		int level;
		Coord location;
		int maxHP;
		std::string name;

	private:
		char symbol;
};