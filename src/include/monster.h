#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "mob.h"
#include "monsterdb.h"

class Level;

class Monster : public Mob {
	public:
		Monster(char, Coord, MonsterDB::MonsterData);
		void attack(Mob*);
		int calculateDamage();
		int getCarryChance();

		int turn(Level*);

	private:
		enum Behaviour {NORMAL};

		int carryChance;
		std::vector<std::pair<int,int>> damage;
};