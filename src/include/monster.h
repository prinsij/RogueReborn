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

		void attack(Mob*);
		int calculateDamage();
		int getCarryChance();
		std::vector<char> getSymbolsForLevel(int);
		std::vector<char> getSymbolsForTreasure(int);

		int turn(Level*);

	private:
		static std::map<char, MONSTER_TUPLE_TYPE> templateMap;

		enum Behaviour {AGGRESSIVE, FLYING, REGENERATIVE, GREEDY, INVISIBLE};

		int carryChance;
		std::vector<std::pair<int,int> > damage;
		std::vector<Behaviour> flags; 
};

// Monster Template Values
std::map<char, MONSTER_TUPLE_TYPE> Monster::templateMap = {
	{'A', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 0, 0)},  20,  "A", 5,std::make_pair( 5,8),      "Aquator",std::make_pair( 8,17)}},
	{'B', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 1, 2)},   1,  "F", 1,std::make_pair( 1,8),          "Bat",std::make_pair( 1, 8)}},
	{'C', MONSTER_TUPLE_TYPE { 4, 15,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  25,   "", 4,std::make_pair( 4,8),      "Centaur",std::make_pair( 7,16)}},
	{'D', MONSTER_TUPLE_TYPE {-1,100,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 3,10)},6800,  "A",10,std::make_pair(10,8),       "Dragon",std::make_pair(22,30)}},
	{'E', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 2)},   2,  "A", 1,std::make_pair( 1,8),          "Emu",std::make_pair( 1, 7)}},
	{'F', MONSTER_TUPLE_TYPE { 3,  0,{std::make_pair( 0, 0)},  80,  "A", 8,std::make_pair( 8,8),"Venus Flytrap",std::make_pair(14,23)}},
	{'G', MONSTER_TUPLE_TYPE { 2, 20,{std::make_pair( 4, 3),
									  std::make_pair( 3, 5),
									  std::make_pair( 4, 3)},2000,"AFR",13,std::make_pair(13,8),      "Griffin",std::make_pair(17,26)}},
	{'H', MONSTER_TUPLE_TYPE { 5,  0,{std::make_pair( 1, 8)},   3,  "A", 1,std::make_pair( 1,8),    "Hobgoblin",std::make_pair( 1, 9)}},
	{'I', MONSTER_TUPLE_TYPE { 9,  0,{std::make_pair( 1, 2)},  15,  "A", 1,std::make_pair( 1,8),  "Ice Monster",std::make_pair( 1,10)}},
	{'J', MONSTER_TUPLE_TYPE { 6, 70,{std::make_pair( 2,12),
									  std::make_pair( 2, 4)},4000,   "",15,std::make_pair(15,8),   "Jabberwock",std::make_pair(21,26)}},
	{'K', MONSTER_TUPLE_TYPE { 7,  0,{std::make_pair( 1, 4)},   1, "AF", 1,std::make_pair( 1,8),      "Kestral",std::make_pair( 1, 6)}},
	{'L', MONSTER_TUPLE_TYPE { 8,100,{std::make_pair( 1, 2)},  10,  "G", 3,std::make_pair( 3,8),   "Leprechaun",std::make_pair( 6,15)}},
	{'M', MONSTER_TUPLE_TYPE { 2, 40,{std::make_pair( 3, 4),
									  std::make_pair( 3, 4),
									  std::make_pair( 2, 5)}, 200,  "A", 8,std::make_pair( 8,8),       "Medusa",std::make_pair(18,26)}},
	{'N', MONSTER_TUPLE_TYPE { 9,100,{std::make_pair( 0, 0)},  37,   "", 3,std::make_pair( 3,8),        "Nymph",std::make_pair(10,19)}},
	{'O', MONSTER_TUPLE_TYPE { 6, 15,{std::make_pair( 1, 8)},   5,  "A", 1,std::make_pair( 1,8),          "Orc",std::make_pair( 3,12)}},
	{'P', MONSTER_TUPLE_TYPE { 2,  0,{std::make_pair( 4, 4)}, 120,  "I", 8,std::make_pair( 8,8),      "Phantom",std::make_pair(15,24)}},
	{'Q', MONSTER_TUPLE_TYPE { 2, 30,{std::make_pair( 1, 2),
									  std::make_pair( 1, 2),
									  std::make_pair( 1, 4)},  32,  "A", 3,std::make_pair( 3,8),       "Quagga",std::make_pair( 9,18)}},
	{'R', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 6)},   9,  "A", 2,std::make_pair( 2,8),  "Rattlesnake",std::make_pair( 4,13)}},
	{'S', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 3)},   1,  "A", 1,std::make_pair( 1,8),        "Snake",std::make_pair( 1,11)}},
	{'T', MONSTER_TUPLE_TYPE { 4, 50,{std::make_pair( 1, 8),
									  std::make_pair( 1, 8),
									  std::make_pair( 2, 6)}, 120, "AR", 6,std::make_pair( 6,8),        "Troll",std::make_pair(12,21)}},
	{'U', MONSTER_TUPLE_TYPE {-2,  0,{std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 1, 3),
									  std::make_pair( 4, 6)}, 190,  "A", 7,std::make_pair( 7,8),      "Ur-Vile",std::make_pair(16,25)}},
	{'V', MONSTER_TUPLE_TYPE { 1, 20,{std::make_pair( 1,10)}, 350, "AR", 8,std::make_pair( 8,8),      "Vampire",std::make_pair(20,26)}},
	{'W', MONSTER_TUPLE_TYPE { 4,  0,{std::make_pair( 1, 6)},  55,   "", 5,std::make_pair( 5,8),       "Wraith",std::make_pair(13,22)}},
	{'X', MONSTER_TUPLE_TYPE { 7, 30,{std::make_pair( 3, 4)}, 100,   "", 7,std::make_pair( 7,8),        "Xeroc",std::make_pair(19,26)}},
	{'Y', MONSTER_TUPLE_TYPE { 6, 30,{std::make_pair( 1, 6),
									  std::make_pair( 1, 6)},  50,   "", 4,std::make_pair( 4,8),         "Yeti",std::make_pair(11,20)}},
	{'Z', MONSTER_TUPLE_TYPE { 8,  0,{std::make_pair( 1, 8)},   6,  "A", 2,std::make_pair( 2,8),       "Zombie",std::make_pair( 3,14)}}
};
