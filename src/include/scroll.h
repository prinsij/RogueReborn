#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name> 
using SCROLL_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Scroll : public Item {
	public:
		static void initializeMap();

		Scroll(Coord);
		Scroll(Coord, Item::Context, int);
		bool activate(Level*);

	private:
		static std::vector<SCROLL_TUPLE_TYPE> typeVector;
		static std::vector<std::string> nameVector;
		static std::vector<std::string> syllableVector;
};

std::vector<SCROLL_TUPLE_TYPE> Scroll::typeVector = {
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

std::vector<std::string> Scroll::nameVector;

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