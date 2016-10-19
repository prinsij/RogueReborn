#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/ring.h"

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

std::vector<std::string> Ring::nameVector = {
	"Diamond Ring",  "Stibotantalite Ring",  "Lapi-Lazuli Ring",  "Ruby Ring",  "Emerald Ring", 
	"Sapphire Ring",  "Amethyst Ring",  "Quartz Ring",  "Tiger-Eye  Ring",  "Opal Ring", 
	"Agate Ring",  "Turquoise Ring",  "Pearl Ring",  "Garnet Ring"
};

void Ring::initializeMap() {
	std::random_shuffle(Ring::nameVector.begin(), Ring::nameVector.end());
}

Ring::Ring(Coord location)
	: Ring(location, Item::Context::FLOOR, rand() % Ring::typeVector.size()) {}

Ring::Ring(Coord location, Item::Context context, int type)
	: Item('=', location, context, "Ring", std::get<0>(Ring::typeVector[type]), Ring::nameVector[type], type, true, true) {}

bool Ring::activate(Level* level) {
	// TODO

	return true;
}
