/**
 * @file ring.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Ring class
 */ 

#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/level.h"
#include "include/playerchar.h"
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
	: Item('=', location, context, "Ring", std::get<0>(Ring::typeVector[type]), Ring::nameVector[type], type, true, true),
	  ringValue(Generator::intFromRange(-2, 2)) {}

bool Ring::activate(Level* level) {
	this->setIdentified(true);

	this->cursed = this->ringValue < 0;

	PlayerChar* player = level->getPlayer();

	// Stealth
	if (this->type == 0) {
		if (!this->cursed)
			player->applyCondition(PlayerChar::STEALTHY, -1);
	// Teleportation
	} else if (this->type == 1) {
		this->cursed = true;
		player->applyCondition(PlayerChar::RANDOM_TELEPORTATION, -1);
	// Regeneration
	} else if (this->type == 2) {
		if (!cursed)
			player->applyCondition(PlayerChar::REGENERATION, -1);
	// Slow Digestion
	} else if (this->type == 3) {
		if (!cursed)
			player->applyCondition(PlayerChar::DIGESTION, -1);
	// Add Strength
	} else if (this->type == 4) {
		int newStrength = std::min(player->getMaxStrength(), player->getStrength() + this->ringValue);
		newStrength = std::max(newStrength, 1);
		player->setStrength(newStrength);	
	// Sustain Strength
	} else if (this->type == 5) {
		if (!this->cursed)
			player->applyCondition(PlayerChar::SUSTAIN_STRENGTH, -1);
	// Dexterity
	} else if (this->type == 6) {
		player->setDexterity(player->getDexterity() + this->ringValue);	
	// Adornment
	} else if (this->type == 7) {
	// See Invisible
	} else if (this->type == 8) {
		player->applyCondition(PlayerChar::SEE_INVISIBLE, -1);
	// Maintain Armor
	} else if (this->type == 9) {
		player->applyCondition(PlayerChar::MAINTAIN_ARMOR, -1);
	// Searching
	} else if (this->type == 10) {
		player->applyCondition(PlayerChar::SEARCH, -1);
	}
	return true;
}
