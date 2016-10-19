#pragma once

#include <string>

#include "coord.h"
#include "item.h"

// <Name> 
using RING_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Ring : public Item {
	public:
		static void initializeMap();

		Ring(Coord);
		Ring(Coord, Item::Context, int);
		bool activate(Level*);

	private:
		static std::vector<RING_TUPLE_TYPE> typeVector;
		static std::vector<std::string> nameVector;
};

std::vector<RING_TUPLE_TYPE> Ring::typeVector = {
	RING_TUPLE_TYPE {"Ring of Stealth"},
	RING_TUPLE_TYPE {"Ring of Teleportation"},
	RING_TUPLE_TYPE {"Ring of Regeneration"},
	RING_TUPLE_TYPE {"Ring of Slow Digestion"},
	RING_TUPLE_TYPE {"Ring of Add Strength"},
	RING_TUPLE_TYPE {"Ring of Sustain Strength"},
	RING_TUPLE_TYPE {"Ring of Dexterity"},
	RING_TUPLE_TYPE {"Ring of Adornment"},
	RING_TUPLE_TYPE {"Ring of See Invisible"},
	RING_TUPLE_TYPE {"Ring of Maintain Armor"},
	RING_TUPLE_TYPE {"Ring of Searching"}
};

std::vector<std::string> Ring::nameVector = {
	"Diamond Ring",  "Stibotantalite Ring",  "Lapi-Lazuli Ring",  "Ruby Ring",  "Emerald Ring", 
	"Sapphire Ring",  "Amethyst Ring",  "Quartz Ring",  "Tiger-Eye  Ring",  "Opal Ring", 
	"Agate Ring",  "Turquoise Ring",  "Pearl Ring",  "Garnet Ring"
};