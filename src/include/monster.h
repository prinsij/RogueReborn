#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "coord.h"
#include "level.h"
#include "mob.h"

using MONSTER_TUPLE_TYPE = std::tuple<int, int, std::vector<std::pair<int, int> >, int, const char*, int, std::pair<int, int>, std::string, std::pair<int, int> >;

//class Level;

class Monster : public Mob {
	public:
		Monster(char, Coord);

		void attack(Level*);
		int calculateDamage();
		int getCarryChance();
		std::vector<char> getSymbolsForLevel(int);
		std::vector<char> getSymbolsForTreasure(int);

		virtual int turn(Level*);

	private:
		static std::map<char, MONSTER_TUPLE_TYPE > templateMap;

		void relocate(Level*);

		enum Behaviour {AGGRESSIVE, FLYING, REGENERATIVE, GREEDY, INVISIBLE};

		int carryChance;
		std::vector<std::pair<int,int> > damage;
		std::vector<Behaviour> flags; 
};

