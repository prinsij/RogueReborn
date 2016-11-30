/**
 * @file potion.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the Potion class
 */ 

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/debug.h"
#include "include/item.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/potion.h"
#include "include/random.h"

std::vector<std::string> Potion::nameVector = Item::shuffleNameVector({
	"Blue Potion", "Red Potion", "Green Potion", "Grey Potion", "Brown Potion",
	"Clear Potion", "Pink Potion", "White Potion", "Purple Potion", "Black Potion",
	"Yellow Potion", "Plaid Potion", "Burgundy Potion", "Beige Potion"
});

std::vector<POTION_TUPLE_TYPE > Potion::typeVector = {
	POTION_TUPLE_TYPE {"Potion of Increase Strength"},
	POTION_TUPLE_TYPE {"Potion of Restore Strength"},
	POTION_TUPLE_TYPE {"Potion of Healing"},
	POTION_TUPLE_TYPE {"Potion of Extra Healing"},
	POTION_TUPLE_TYPE {"Potion of Poison"},
	POTION_TUPLE_TYPE {"Potion of Raise Level"},
	POTION_TUPLE_TYPE {"Potion of Blindness"},
	POTION_TUPLE_TYPE {"Potion of Hallucination"},
	POTION_TUPLE_TYPE {"Potion of Detect Monster"},
	POTION_TUPLE_TYPE {"Potion of Detect Things"},
	POTION_TUPLE_TYPE {"Potion of Confusion"},
	POTION_TUPLE_TYPE {"Potion of Levitation"},
	POTION_TUPLE_TYPE {"Potion of Haste Self"},
	POTION_TUPLE_TYPE {"Potion of See Invisible"}
};

Potion::Potion(Coord location)
	: Potion(location, Item::Context::FLOOR, Generator::intFromRange(0, Potion::typeVector.size() - 1)) {}

Potion::Potion(Coord location, Item::Context context, int type)
	: Item('!', location, context, "Potion", std::get<0>(Potion::typeVector[type]), 
	Potion::nameVector[type], type, true, true, POTION_WEIGHT) {}

bool Potion::activate(Mob* mob) {
	this->setIdentified(true);

	PlayerChar* player = dynamic_cast<PlayerChar*>(mob);

	// Increase Strength
	if (this->type == 0) {
		if (player == NULL) {
			return false;
		}
		player->appendLog("You feel stronger now, what bulging muscles!");

		if (player->getMaxStrength() == player->getStrength()) {
			player->changeMaxStrength(1);
		}
		player->changeCurrentStrength(1);

	// Restore Strength
	} else if (this->type == 1) {
		if (player == NULL) {
			return false;
		}
		PlayerChar* player = dynamic_cast<PlayerChar*>(mob);
		player->appendLog("This tastes great; you feel warm all over");

		int strengthLeft = player->getMaxStrength() - player->getStrength();
		player->changeCurrentStrength(strengthLeft);

	// Healing / Extra Healing
	} else if (this->type == 2 || this->type == 3) {
		if (player != NULL) {
			if (this->type == 2) {
				player->appendLog("You begin to feel better");
			} else {
				player->appendLog("You begin to feel much better");
			}
		}

		int difference = this->type - 2;
		float ratio = static_cast<float>(mob->getHP())/mob->getMaxHP();

		if (ratio >= 1.00) {
			mob->setMaxHP(mob->getMaxHP() + 1 + difference);
			mob->setCurrentHP(mob->getMaxHP());
		} else if (ratio >= 0.90) {
			mob->setMaxHP(mob->getMaxHP() + difference);
			mob->setCurrentHP(mob->getMaxHP());
		} else {
			ratio = std::max(static_cast<float>(0.33), ratio);
			if (difference == 1) ratio *= 2;
				int deltaHP = static_cast<int>(ratio*(mob->getMaxHP() - mob->getHP()));
				mob->setCurrentHP(std::min(mob->getHP() + deltaHP, mob->getMaxHP()));
			}

	// Poison
	} else if (this->type == 4) {
		if (!player) return false;

		player->appendLog("You feel very sick now");

		if (!player->hasCondition(PlayerChar::SUSTAIN_STRENGTH)) {
			int newStrength = player->getStrength();
			newStrength = std::max(1, newStrength - Generator::intFromRange(1, 3));
			player->changeCurrentStrength(newStrength - player->getStrength());
		}

		player->removeCondition(PlayerChar::HALLUCINATING);

	// Raise Level
	} else if (this->type == 5) {
		if (!player) return false;

		player->appendLog("You suddenly feel much more skillful");
		player->raiseLevel();

	// Blindness
	} else if (this->type == 6) {
		if (!player) return false;

		if (!player->hasCondition(PlayerChar::BLIND)) {
			player->appendLog("A cloak of darkness falls around you");
		}

		player->applyCondition(PlayerChar::BLIND, Generator::intFromRange(500, 800));

	// Hallucination
	} else if (this->type == 7) {
		if (!player) return false;

		player->appendLog("Oh wow, everything seems so cosmic!");

		player->applyCondition(PlayerChar::HALLUCINATING, Generator::intFromRange(500, 800));

	// Detect Monster
	} else if (this->type == 8) {
		if (!player) return false;

		player->appendLog("You have a strange feeling for moment, then it passes");

		player->applyCondition(PlayerChar::DETECT_MONSTER, -1);

	// Detect Objects
	} else if (this->type == 9) {
		if (!player) return false;

		player->appendLog("You have a strange feeling for moment, then it passes");

		player->applyCondition(PlayerChar::DETECT_OBJECTS, -1);

	// Confusion
	} else if (this->type == 10) {
		if (!player) return false;

		player->appendLog(player->hasCondition(PlayerChar::HALLUCINATING) ? "What a trippy feeling" : "You feel confused");

		player->applyCondition(PlayerChar::CONFUSED, Generator::intFromRange(12, 22));

	// Levitation
	} else if (this->type == 11) {
		if (!player) return false;

		player->appendLog("You start to float in the air");

		player->applyCondition(PlayerChar::LEVITATING, Generator::intFromRange(15, 30));
		player->removeCondition(PlayerChar::IMMOBILIZED);

	// Haste
	} else if (this->type == 12) {
		if (!player) return false;

		player->appendLog("You feel yourself moving much faster");

		player->applyCondition(PlayerChar::HASTED, Generator::intFromRange(11, 21));

	// See Invisible
	} else if (this->type == 13) {
		if (!player) return false;

		player->appendLog("Hmm, this potion tastes like fruit juice");

		player->removeCondition(PlayerChar::BLIND);
		player->applyCondition(PlayerChar::SEE_INVISIBLE, -1);
	} else {
#ifdef DEBUG
		std::cout << "Invalid Potion Type: " << this->type << "\n";
#endif
	}

	return true;
}
