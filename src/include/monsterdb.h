#pragma once

#include <map>
#include <string>

class MonsterDB {
	public:
		struct MonsterData {
			int armor;
			int carryChance;
			std::vector<std::pair<int, int>> damage;
			int exp;
			const char* flags;
			int level;
			std::pair<int, int> hpBounds;
			std::string name;
			std::pair<int, int> range;
		};

		void initialize();
		MonsterData getData(char);
		
	private:
		static std::map<char, MonsterData> monsterMap;
		static MonsterData NULL_DATA;
};
