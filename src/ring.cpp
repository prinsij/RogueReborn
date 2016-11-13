/**
 * @file ring.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the Ring class
 */ 

#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/random.h"
#include "include/ring.h"

std::vector<std::string> Ring::nameVector = Item::shuffleNameVector({
	"Diamond Ring",  "Stibotantalite Ring",  "Lapi-Lazuli Ring",  "Ruby Ring",  "Emerald Ring",
	"Sapphire Ring",  "Amethyst Ring",  "Quartz Ring",  "Tiger-Eye  Ring",  "Opal Ring",
	"Agate Ring",  "Turquoise Ring",  "Pearl Ring",  "Garnet Ring"
});

std::vector<RING_TUPLE_TYPE > Ring::typeVector = {
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

Ring::Ring(Coord location)
	: Ring(location, Item::Context::FLOOR, Generator::intFromRange(0, Ring::typeVector.size() - 1)) {}

Ring::Ring(Coord location, Item::Context context, int type)
	: Item('=', location, context, "Ring", std::get<0>(Ring::typeVector[type]), Ring::nameVector[type], type, true, true) {}

bool Ring::activate(Level* level) {
	return false;
}