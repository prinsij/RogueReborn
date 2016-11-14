/**
 * @file trap.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Trap class
 */ 

#include "include/coord.h"
#include "include/feature.h"
#include "include/playerchar.h"
#include "include/random.h"
#include "include/trap.h"

Trap::Trap(Coord location, unsigned char type, bool visible)
	: Feature('^', location),
	  type(type),
	  visible(visible) {}

/*
		   0 = Door Trap
		   1 = Rust Trap
		   2 = Sleep Trap
		   3 = Bear Trap
		   4 = Teleport Trap
		   5 = Dart Trap
*/
void Trap::activate(Mob* mob) {
	PlayerChar* player = dynamic_cast<PlayerChar*>(mob);

	if (player) {
		if (Generator::intFromRange(0,99) <= player->getLevel() + player->getDexterity()) {
			player->appendLog("The trap failed");
			return;
		}
	}

	// Door Trap
	if (this->type == 0) {
		if (!player) return;

		player->appendLog("You fell down a trap");
		
		// TODO

	// Rust Trap
	} else if (this->type == 1) {
		mob->hit(Generator::intFromRange(1, 6));

		if (player) {
			player->appendLog("A gush of water hits you on the head");

			// TODO
		}

	// Sleep Trap
	} else if (this->type == 2) {
		if (!player) return;

		player->appendLog("A strange white mist envelops you and you fall asleep");
		player->applyCondition(PlayerChar::SLEEPING, Generator::intFromRange(2, 5));

	// Bear Trap
	} else if (this->type == 3) {
		if (!player) return;

		player->appendLog("You are caught in a bear trap");
		player->applyCondition(PlayerChar::IMMOBILIZED, Generator::intFromRange(4, 7));

	// Teleport Trap
	} else if (this->type == 4) {
		if (player) {
			player->appendLog("You are suddenly taken aback");
		}

		// TODO

	// Dart Trap
	} else if (this->type == 5) {
		mob->hit(Generator::intFromRange(1, 6));

		if (player) {
			player->appendLog("A small dart just hit you in the shoulder");

			if (!player->hasCondition(PlayerChar::SUSTAIN_STRENGTH) && 
				Generator::intFromRange(0, 99) <= 40 &&
				player->getStrength() >= 3) {
				player->changeCurrentStrength(-1);
			}
		}
	}

}