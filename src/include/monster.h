#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "mob.h"
#include "monsterdb.h"

class Monster : public Mob {
	public:
		Monster(char, Coord, MonsterDB::MonsterData);
		void attack(Mob &);
		int calculateDamage();
		int getCarryChance();

	private:
		enum Behaviour {NORMAL};

		int carryChance;
		std::vector<std::pair<int,int>> damage;

		int diceSum(int, int);
};
