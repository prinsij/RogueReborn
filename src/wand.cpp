/**
 * @file wand.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Wand class
 */ 

#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/random.h"
#include "include/wand.h"

std::vector<WAND_TUPLE_TYPE > Wand::typeVector = {
	WAND_TUPLE_TYPE {"Wand of Teleport Away"},
	WAND_TUPLE_TYPE {"Wand of Slow Monster"},
	WAND_TUPLE_TYPE {"Wand of Invisibility"},
	WAND_TUPLE_TYPE {"Wand of Polymorph"},
	WAND_TUPLE_TYPE {"Wand of Haste Monster"},
	WAND_TUPLE_TYPE {"Wand of Magic Missile"},
	WAND_TUPLE_TYPE {"Wand of Cancellation"},
	WAND_TUPLE_TYPE {"Wand of Do Nothing"},
	WAND_TUPLE_TYPE {"Wand of Drain Life"},
	WAND_TUPLE_TYPE {"Wand of Cold"},
	WAND_TUPLE_TYPE {"Wand of Fire"}
};

std::vector<std::string> Wand::nameVector = Item::shuffleNameVector({
	"Steel Wand", "Bronze Wand", "Gold Wand", "Silver Wand", "Copper Wand",
	"Nickel Wand", "Cobalt Wand", "Tin Wand", "Iron Wand", "Magnesium Wand",
	"Chrome Wand", "Carbon Wand", "Platinum Wand", "Silicon Wand", "Titanium Wand",
	"Teak Wand", "Oak Wand", "Cherry Wand", "Birch Wand", "Pine Wand",
	"Cedar Wand", "Redwood Wand", "Balsa Wand", "Ivory Wand", "Walnut Wand",
	"Maple Wand", "Mahogany Wand", "Elm Wand", "Palm Wand", "Wooden Wand"
});


Wand::Wand(Coord location)
	: Wand(location, Item::Context::FLOOR, Generator::intFromRange(0, Wand::typeVector.size() - 1)) {}

Wand::Wand(Coord location, Item::Context context, int type)
	: Item('/', location, context, "Wand", std::get<0>(Wand::typeVector[type]), Wand::nameVector[type], type, false, false),
	  charges(Generator::intFromRange(3, 7)) {}

bool Wand::activate(Level* level, Mob* mob) {
	this->setIdentified(true);

	PlayerChar* player = level->getPlayer();
	Monster* monster = dynamic_cast<Monster*>(mob); 

	this->charges--;

	// Teleport Away
	if (this->type == 0) {
		// TODO

	// Slow Monster
	} else if (this->type == 1) {
		monster->addFlag(Monster::SLOWED);

	// Invisibility
	} else if (this->type == 2) {
		// Find Monster
		// TODO

	// Polymorph
	} else if (this->type == 3) {
		// TODO

	// Haste Monster
	} else if (this->type == 4) {
		monster->addFlag(Monster::HASTED);

	// Magic Missile
	} else if (this->type == 5) {
		monster->hit(player->calculateDamage());

	// Cancellation
	} else if (this->type == 6) {
		monster->addFlag(Monster::CANCELLED);

	// Do Nothing
	} else if (this->type == 7) {
		player->appendLog("Nothing happens");

	// Drain Life
	} else if (this->type == 8) {
		int monsterDamage = player->getHP()/3;
		player->setCurrentHP((player->getHP() + 1)/2);
		monster->hit(monsterDamage);

	// Cold
	} else if (this->type == 9) {
		if (Generator::intFromRange(0, 99) <= 33) {
			player->appendLog("The ice ball misses the " + monster->getName());
			return false;
		}

		int damage = 0;

		if (monster->hasFlag(Monster::RUSTS)) {
			damage = monster->getHP()/2 + 1;
		} else {
			if (monster->hasFlag(Monster::FREEZES)) {
				damage = monster->getHP();
			} else if (monster->hasFlag(Monster::FLAMES)) {
				damage = monster->getHP()/10 + 1;
			} else {
				damage = Generator::intFromRange(player->getHP()/3, player->getMaxHP());
			}
		}

		player->appendLog("The ice ball hits the " + monster->getName());

		monster->hit(damage);

	// Fire
	} else if (this->type == 10) {
		if (Generator::intFromRange(0, 99) <= 33) {
			player->appendLog("The fire ball misses the " + monster->getName());
			return false;
		}

		int damage = 0;

		if (monster->hasFlag(Monster::FLAMES)) {
			damage = monster->getHP();
		} else if (monster->hasFlag(Monster::FREEZES)) {
			damage = monster->getHP()/10 + 1;
		} else {
			damage = Generator::intFromRange(player->getHP()/3, player->getMaxHP());
		}

		player->appendLog("The fire ball hits the " + monster->getName());

		monster->hit(damage);
	}

	return true;
}

int Wand::getCharges() {
	return this->charges;
}
