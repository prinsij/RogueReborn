#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "coord.h"
#include "mob.h"

using TUPLE_TYPE = std::tuple<int, int, std::vector<std::pair<int, int>>, int, const char*, int, std::pair<int, int>, std::string>;

class Level;

class Monster : public Mob {
	public:
		Monster(char, Coord);

		void attack(Mob*);
		int calculateDamage();
		int getCarryChance();

		int turn(Level*);

	private:
		static std::map<char, TUPLE_TYPE> templateMap;

		enum Behaviour {AGGRESSIVE, FLYING, REGENERATIVE, GREEDY, INVISIBLE};

		int carryChance;
		std::vector<std::pair<int,int>> damage;
		std::vector<Behaviour> flags; 
};

// Monster Template Values
std::map<char, TUPLE_TYPE> Monster::templateMap = {
	{'A', TUPLE_TYPE { 2,  0,{std::make_pair( 0, 0)},  20,  "A", 5, std::make_pair( 5,8),      "Aquator"}},
	{'B', TUPLE_TYPE { 3,  0,{std::make_pair( 1, 2)},   1,  "F", 1, std::make_pair( 1,8),          "Bat"}},
	{'C', TUPLE_TYPE { 4, 15,{std::make_pair( 1, 6),
							  std::make_pair( 1, 6)},  25,   "", 4, std::make_pair( 4,8),      "Centaur"}},
	{'D', TUPLE_TYPE {-1,100,{std::make_pair( 1, 8),
							  std::make_pair( 1, 8),
							  std::make_pair( 3,10)},6800,  "A",10, std::make_pair(10,8),       "Dragon"}},
	{'E', TUPLE_TYPE { 7,  0,{std::make_pair( 1, 2)},   2,  "A", 1, std::make_pair( 1,8),          "Emu"}},
	{'F', TUPLE_TYPE { 3,  0,{std::make_pair( 0, 0)},  80,  "A", 8, std::make_pair( 8,8),"Venus Flytrap"}},
	{'G', TUPLE_TYPE { 2, 20,{std::make_pair( 4, 3),
							  std::make_pair( 3, 5),
							  std::make_pair( 4, 3)},2000,"AFR",13, std::make_pair(13,8),      "Griffin"}},
	{'H', TUPLE_TYPE { 5,  0,{std::make_pair( 1, 8)},   3,  "A", 1, std::make_pair( 1,8),    "Hobgoblin"}},
	{'I', TUPLE_TYPE { 9,  0,{std::make_pair( 1, 2)},  15,  "A", 1, std::make_pair( 1,8),  "Ice Monster"}},
	{'J', TUPLE_TYPE { 6, 70,{std::make_pair( 2,12),
							  std::make_pair( 2, 4)},4000,   "",15, std::make_pair(15,8),   "Jabberwock"}},
	{'K', TUPLE_TYPE { 7,  0,{std::make_pair( 1, 4)},   1, "AF", 1, std::make_pair( 1,8),      "Kestral"}},
	{'L', TUPLE_TYPE { 8,100,{std::make_pair( 1, 2)},  10,  "G", 3, std::make_pair( 3,8),   "Leprechaun"}},
	{'M', TUPLE_TYPE { 2, 40,{std::make_pair( 3, 4),
							  std::make_pair( 3, 4),
							  std::make_pair( 2, 5)}, 200,  "A", 8, std::make_pair( 8,8),       "Medusa"}},
	{'N', TUPLE_TYPE { 9,100,{std::make_pair( 0, 0)},  37,   "", 3, std::make_pair( 3,8),        "Nymph"}},
	{'O', TUPLE_TYPE { 6, 15,{std::make_pair( 1, 8)},   5,  "A", 1, std::make_pair( 1,8),          "Orc"}},
	{'P', TUPLE_TYPE { 2,  0,{std::make_pair( 4, 4)}, 120,  "I", 8, std::make_pair( 8,8),      "Phantom"}},
	{'Q', TUPLE_TYPE { 2, 30,{std::make_pair( 1, 2),
							  std::make_pair( 1, 2),
							  std::make_pair( 1, 4)},  32,  "A", 3, std::make_pair( 3,8),       "Quagga"}},
	{'R', TUPLE_TYPE { 8,  0,{std::make_pair( 1, 6)},   9,  "A", 2, std::make_pair( 2,8),  "Rattlesnake"}},
	{'S', TUPLE_TYPE { 8,  0,{std::make_pair( 1, 3)},   1,  "A", 1, std::make_pair( 1,8),        "Snake"}},
	{'T', TUPLE_TYPE { 4, 50,{std::make_pair( 1, 8),
							  std::make_pair( 1, 8),
							  std::make_pair( 2, 6)}, 120, "AR", 6, std::make_pair( 6,8),        "Troll"}},
	{'U', TUPLE_TYPE {-2,  0,{std::make_pair( 1, 3),
							  std::make_pair( 1, 3),
							  std::make_pair( 1, 3),
							  std::make_pair( 4, 6)}, 190,  "A", 7, std::make_pair( 7,8),      "Ur-Vile"}},
	{'V', TUPLE_TYPE { 1, 20,{std::make_pair( 1,10)}, 350, "AR", 8, std::make_pair( 8,8),      "Vampire"}},
	{'W', TUPLE_TYPE { 4,  0,{std::make_pair( 1, 6)},  55,   "", 5, std::make_pair( 5,8),       "Wraith"}},
	{'X', TUPLE_TYPE { 7, 30,{std::make_pair( 3, 4)}, 100,   "", 7, std::make_pair( 7,8),        "Xeroc"}},
	{'Y', TUPLE_TYPE { 6, 30,{std::make_pair( 1, 6),
							  std::make_pair( 1, 6)},  50,   "", 4, std::make_pair( 4,8),         "Yeti"}},
	{'Z', TUPLE_TYPE { 8,  0,{std::make_pair( 1, 8)},   6,  "A", 2, std::make_pair( 2,8),       "Zombie"}}
};