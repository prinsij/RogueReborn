#include <string>
#include "coord.h"
#include "itemzone.h"

class PlayerChar {
	public:
		int getStrength();
		int getArmor();
		std::string getName();
		int getGold();
		int getHP();
		int getMaxHP();
		Coord getCoord();
		int getLevel();
	private:
		int HP;
		int maxHP;
		int armor;
		int strength;
		int gold;
		std::string name;
		Coord coord;
		ItemZone backpack;
		int level;
}
