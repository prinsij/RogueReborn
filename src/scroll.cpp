#include <algorithm>
#include <string>
#include <vector>

#include "include/coord.h"
#include "include/item.h"
#include "include/scroll.h"

void Scroll::initializeMap() {
	for (int type = 0 ; type < static_cast<int>(Scroll::typeVector.size()) ; type++) {
		std::string scrollName = "Scroll titled '";
		scrollName += Scroll::syllableVector[rand() % Scroll::syllableVector.size()];

		int syllables = 1 + (rand() % 3);

		for (int syll = 0 ; syll < syllables ; syll++) {
			scrollName += " " + Scroll::syllableVector[rand() % Scroll::syllableVector.size()];
		}

		scrollName += "'";
		Scroll::nameVector.push_back(scrollName);
	}
}

Scroll::Scroll(Coord location)
	: Scroll(location, Item::Context::FLOOR, rand() % Scroll::typeVector.size()) {}

Scroll::Scroll(Coord location, Item::Context context, int type)
	: Item('?', location, context, "Scroll", std::get<0>(Scroll::typeVector[type]), Scroll::nameVector[type], type, true, true) {}

bool Scroll::activate(Level* level) {
	// TODO

	return true;
}