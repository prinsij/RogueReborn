/**
 * @file scroll.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member definitions for the Scroll class
 */ 

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/coord.h"
#include "include/invscreen.h"
#include "include/item.h"
#include "include/level.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/random.h"
#include "include/ring.h"
#include "include/scroll.h"
#include "include/terrain.h"
#include "include/uistate.h"
#include "include/weapon.h"
#include "test.testable.h"

std::vector<SCROLL_TUPLE_TYPE > Scroll::typeVector = {
	SCROLL_TUPLE_TYPE {"Scroll of Protect Armor"},
	SCROLL_TUPLE_TYPE {"Scroll of Hold Monster"},
	SCROLL_TUPLE_TYPE {"Scroll of Enchant Weapon"},
	SCROLL_TUPLE_TYPE {"Scroll of Enchant Armor"},
	SCROLL_TUPLE_TYPE {"Scroll of Identify"},
	SCROLL_TUPLE_TYPE {"Scroll of Teleportation"},
	SCROLL_TUPLE_TYPE {"Scroll of Sleep"},
	SCROLL_TUPLE_TYPE {"Scroll of Scare Monster"},
	SCROLL_TUPLE_TYPE {"Scroll of Remove Curse"},
	SCROLL_TUPLE_TYPE {"Scroll of Create Monster"},
	SCROLL_TUPLE_TYPE {"Scroll of Aggravate Monster"},
	SCROLL_TUPLE_TYPE {"Scroll of Magic Mapping"},
	SCROLL_TUPLE_TYPE {"Scroll of Confuse Monster"}
};

std::vector<std::string> Scroll::syllableVector = {
	"Blech", "Foo", "Barf", "Rech", "Bar",
	"Quo", "Bloto", "Oh", "Caca", "Blorp",
	"Erp", "Festr", "Rot", "Slie", "Snorf",
	"Iky", "Yuky", "Ooze", "Ah", "Bahl",
	"Zep", "Druhl", "Flem", "Behil", "Arek",
	"Mep", "Zihr", "Grit", "Kona", "Kini",
	"Ichi", "Tims", "Ogr", "Oo", "Ighr",
	"Coph", "Swerr", "Mihln", "Poxi"
};

bool Scroll::ignoreTransitions = false;

std::vector<std::string> Scroll::nameVector = Scroll::initializeScrollNames();

std::vector<std::string> Scroll::initializeScrollNames() {
	std::vector<std::string> nameVector;
	for (int type = 0 ; type < static_cast<int>(Scroll::typeVector.size()) ; type++) {
		std::string scrollName = "Scroll titled '";
		scrollName += Scroll::syllableVector[Generator::intFromRange(0, Scroll::syllableVector.size() - 1)];

		int syllables = Generator::intFromRange(1, 3);

		for (int syll = 0 ; syll < syllables ; syll++) {
			scrollName += " " + Scroll::syllableVector[Generator::intFromRange(0, Scroll::syllableVector.size() - 1)];
		}

		scrollName += "'";
		nameVector.push_back(scrollName);
	}

	return nameVector;
}

Scroll::Scroll(Coord location)
	: Scroll(location, Item::Context::FLOOR, Generator::intFromRange(0, Scroll::typeVector.size() - 1)) {}

Scroll::Scroll(Coord location, Item::Context context, int type)
	: Item('?', location, context, "Scroll", std::get<0>(Scroll::typeVector[type]),
			Scroll::nameVector[type], type, true, true, SCROLL_WEIGHT) {}

std::tuple<bool, UIState*> Scroll::activate(Level* level) {
	this->setIdentified(true);

	PlayerChar* player = level->getPlayer();

	UIState* nextState = Scroll::ignoreTransitions ? NULL : new PlayState(player, level);

	// Protect Armor
	if (this->type == 0) {
		Armor* armor = player->getArmor();

		if (armor == NULL) {
			player->appendLog("Your acne seems to have disappeared");
		} else {
			player->appendLog("Your armor is covered by a shimmering gold shield");
			armor->applyEffect(Item::PROTECTED);
			armor->removeEffect(Item::CURSED);
		}

	// Hold Monster
	} else if (this->type == 1) {
		int nearbyMonsters = 0;

		for (Mob* mob : level->getMobs()) {
			Monster* monster = dynamic_cast<Monster*>(mob);

			if (monster && player->getLocation().distanceTo(monster->getLocation()) <= 8) {
				nearbyMonsters ++;
				monster->addFlag(Monster::HELD);
			}
		}

		if (nearbyMonsters == 0) {
			player->appendLog("You feel a strange sense of loss");
		} else if (nearbyMonsters == 1) {
			player->appendLog("The monster freezes");
		} else {
			player->appendLog("The monsters around you freeze");
		}

	// Enchant Weapon
	} else if (this->type == 2) {
		Weapon* weapon = player->getWeapon();

		if (weapon == NULL) {
			player->appendLog("Your hands tingle");
		} else {
			std::string colour = Generator::randBool() ? "red" : "blue";
			player->appendLog("Your hands glow " + colour + " for a moment");

			std::pair<int,int> enchantments = weapon->getEnchantments();

			if (Generator::randBool()) {
				enchantments.first++;
			} else {
				enchantments.second++;
			}

			weapon->setEnchantments(enchantments.first, enchantments.second);
			weapon->removeEffect(Item::CURSED);
		}

	// Enchant Armor
	} else if (this->type == 3) {
		Armor* armor = player->getArmor();

		if (armor == NULL) {
			player->appendLog("Your skin crawls");
		} else {
			std::string colour = Generator::randBool() ? "red" : "blue";
			player->appendLog("Your armor glows " + colour + " for a moment");

			armor->setEnchantment(armor->getEnchantment() + 1);
			armor->removeEffect(Item::CURSED);
		}

	// Identify
	} else if (this->type == 4) {
		player->appendLog("This is a scroll of identify");
		for (auto pair : player->getInventory().getContents()) {
			if (!pair.second.front()->isIdentified()) {
				if (!Scroll::ignoreTransitions) {
					delete nextState;
					nextState = new InvScreen(player, level, [] (Item* i) {return !i->isIdentified();},
														  [] (Item* i, PlayerChar* p, Level* l) {
																i->setIdentified(true);
																return new PlayState(p, l);
															},
															false,
															"Choose an item to identify");
				}
			}
		}

	// Teleportation
	} else if (this->type == 5) {
		player->setLocation(level->getRandomEmptyPosition());

	// Sleep
	} else if (this->type == 6) {
		player->appendLog("Your fall asleep");
		player->applyCondition(PlayerChar::SLEEPING, Generator::intFromRange(2, 5));

	// Scare Monster
	} else if (this->type == 7) {
		player->appendLog("You hear a maniacal laughter in the distance");

	// Remove Curse
	} else if (this->type == 8) {
		player->appendLog(player->hasCondition(PlayerChar::HALLUCINATING) ?
			"You feel in touch with the universal oneness" :
			"You feel as though someone is watching over you");

		Armor* armor = player->getArmor();
		Weapon* weapon = player->getWeapon();
		std::pair<Ring*, Ring*> rings = player->getRings();

		if (armor != NULL) armor->removeEffect(Item::CURSED);
		if (weapon != NULL) weapon->removeEffect(Item::CURSED);
		if (rings.first != NULL) rings.first->removeEffect(Item::CURSED);
		if (rings.second != NULL) rings.second->removeEffect(Item::CURSED);

	// Create Monster
	} else if (this->type == 9) {
		player->appendLog("You hear a faint cry of anguish in the distance");
		level->putRandomMonster();

	// Aggravate Monster
	} else if (this->type == 10) {
		player->appendLog("You hear a high pitched humming noise");
		for (auto mob : level->getMobs()) {
			auto monster = dynamic_cast<Monster*>(mob);
			if (monster != NULL) {
				monster->aggrevate();
			}
		}

	// Magic Mapping
	} else if (this->type == 11) {
		player->appendLog("This scroll seems to have a map on it");
		for (auto x=0; x < level->getSize()[0]; ++x) {
			for (auto y=0; y < level->getSize()[1]; ++y) {
				level->tileAt(Coord(x,y)).setIsSeen(Terrain::Seen);
			}
		}

	// Confuse Monster
	} else if (this->type == 12) {
		std::string colour = Generator::randBool() ? "red" : "blue";
		player->appendLog("Your armor glows " + colour + " for a moment");

		player->applyCondition(PlayerChar::CONFUSE_MONSTER, -1);
	}

	return std::tuple<bool, UIState*>(true, nextState);
}
