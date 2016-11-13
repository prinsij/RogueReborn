/**
 * @file scroll.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Scroll class
 */ 

#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/random.h"
#include "include/scroll.h"

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
	: Item('?', location, context, "Scroll", std::get<0>(Scroll::typeVector[type]), Scroll::nameVector[type], type, true, true) {}

bool Scroll::activate(Level* level) {
	// TODO

	return true;
}