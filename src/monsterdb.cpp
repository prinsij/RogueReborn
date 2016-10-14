#include <algorithm>
#include <map>
#include <string>

#include "include/monsterdb.h"

MonsterDB::MonsterData MonsterDB::NULL_DATA;
std::map<char, MonsterDB::MonsterData> MonsterDB::monsterMap;

void MonsterDB::initialize() {
	NULL_DATA = MonsterData {-1, -1, {std::make_pair(-1, -1)}, -1, "", -1, std::make_pair(-1, -1), "NULL", std::make_pair(-1, -1)};

	monsterMap.clear();
	monsterMap['A'] = MonsterData{ 2,  0,{std::make_pair( 0, 0)},  20,  "A", 5, std::make_pair( 5,8),      "Aquator",std::make_pair( 8,17)};
	monsterMap['B'] = MonsterData{ 3,  0,{std::make_pair( 1, 2)},   1,  "F", 1, std::make_pair( 1,8),          "Bat",std::make_pair( 1, 8)};
	monsterMap['C'] = MonsterData{ 4, 15,{std::make_pair( 1, 6),
										  std::make_pair( 1, 6)},  25,   "", 4, std::make_pair( 4,8),      "Centaur",std::make_pair( 7,16)};
	monsterMap['D'] = MonsterData{-1,100,{std::make_pair( 1, 8),
										  std::make_pair( 1, 8),
										  std::make_pair( 3,10)},6800,  "A",10, std::make_pair(10,8),       "Dragon",std::make_pair(22,30)};
	monsterMap['E'] = MonsterData{ 7,  0,{std::make_pair( 1, 2)},   2,  "A", 1, std::make_pair( 1,8),          "Emu",std::make_pair( 1, 7)};
	monsterMap['F'] = MonsterData{ 3,  0,{std::make_pair( 0, 0)},  80,  "A", 8, std::make_pair( 8,8),"Venus Flytrap",std::make_pair(14,23)};
	monsterMap['G'] = MonsterData{ 2, 20,{std::make_pair( 4, 3),
										  std::make_pair( 3, 5),
										  std::make_pair( 4, 3)},2000,"AFR",13, std::make_pair(13,8),      "Griffin",std::make_pair(17,26)};
	monsterMap['H'] = MonsterData{ 5,  0,{std::make_pair( 1, 8)},   3,  "A", 1, std::make_pair( 1,8),    "Hobgoblin",std::make_pair( 1, 9)};
	monsterMap['I'] = MonsterData{ 9,  0,{std::make_pair( 1, 2)},  15,  "A", 1, std::make_pair( 1,8),  "Ice Monster",std::make_pair( 1,10)};
	monsterMap['J'] = MonsterData{ 6, 70,{std::make_pair( 2,12),
										  std::make_pair( 2, 4)},4000,   "",15, std::make_pair(15,8),   "Jabberwock",std::make_pair(21,26)};
	monsterMap['K'] = MonsterData{ 7,  0,{std::make_pair( 1, 4)},   1, "AF", 1, std::make_pair( 1,8),      "Kestral",std::make_pair( 1, 6)};
	monsterMap['L'] = MonsterData{ 8,100,{std::make_pair( 1, 2)},  10,  "G", 3, std::make_pair( 3,8),   "Leprechaun",std::make_pair( 6,15)};
	monsterMap['M'] = MonsterData{ 2, 40,{std::make_pair( 3, 4),
										  std::make_pair( 3, 4),
										  std::make_pair( 2, 5)}, 200,  "A", 8, std::make_pair( 8,8),       "Medusa",std::make_pair(18,26)};
	monsterMap['N'] = MonsterData{ 9,100,{std::make_pair( 0, 0)},  37,   "", 3, std::make_pair( 3,8),        "Nymph",std::make_pair(10,19)};
	monsterMap['O'] = MonsterData{ 6, 15,{std::make_pair( 1, 8)},   5,  "A", 1, std::make_pair( 1,8),          "Orc",std::make_pair( 3,12)};
	monsterMap['P'] = MonsterData{ 2,  0,{std::make_pair( 4, 4)}, 120,  "I", 8, std::make_pair( 8,8),      "Phantom",std::make_pair(15,24)};
	monsterMap['Q'] = MonsterData{ 2, 30,{std::make_pair( 1, 2),
										  std::make_pair( 1, 2),
										  std::make_pair( 1, 4)},  32,  "A", 3, std::make_pair( 3,8),       "Quagga",std::make_pair( 9,18)};
	monsterMap['R'] = MonsterData{ 8,  0,{std::make_pair( 1, 6)},   9,  "A", 2, std::make_pair( 2,8),  "Rattlesnake",std::make_pair( 4,13)};
	monsterMap['S'] = MonsterData{ 8,  0,{std::make_pair( 1, 3)},   1,  "A", 1, std::make_pair( 1,8),        "Snake",std::make_pair( 1,11)};
	monsterMap['T'] = MonsterData{ 4, 50,{std::make_pair( 1, 8),
										  std::make_pair( 1, 8),
										  std::make_pair( 2, 6)}, 120, "AR", 6, std::make_pair( 6,8),        "Troll",std::make_pair(12,21)};
	monsterMap['U'] = MonsterData{-2,  0,{std::make_pair( 1, 3),
										  std::make_pair( 1, 3),
										  std::make_pair( 1, 3),
										  std::make_pair( 4, 6)}, 190,  "A", 7, std::make_pair( 7,8),      "Ur-Vile",std::make_pair(16,25)};
	monsterMap['V'] = MonsterData{ 1, 20,{std::make_pair( 1,10)}, 350, "AR", 8, std::make_pair( 8,8),      "Vampire",std::make_pair(20,26)};
	monsterMap['W'] = MonsterData{ 4,  0,{std::make_pair( 1, 6)},  55,   "", 5, std::make_pair( 5,8),       "Wraith",std::make_pair(13,22)};
	monsterMap['X'] = MonsterData{ 7, 30,{std::make_pair( 3, 4)}, 100,   "", 7, std::make_pair( 7,8),        "Xeroc",std::make_pair(19,26)};
	monsterMap['Y'] = MonsterData{ 6, 30,{std::make_pair( 1, 6),
										  std::make_pair( 1, 6)},  50,   "", 4, std::make_pair( 4,8),         "Yeti",std::make_pair(11,20)};
	monsterMap['Z'] = MonsterData{ 8,  0,{std::make_pair( 1, 8)},   6,  "A", 2, std::make_pair( 2,8),       "Zombie",std::make_pair( 3,14)};
}

MonsterDB::MonsterData MonsterDB::getData(char symbol) {
	auto mapIt = monsterMap.find(symbol);

	return mapIt != monsterMap.end() ? mapIt->second : NULL_DATA; 
}