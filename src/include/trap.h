/**
 * @file trap.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the Trap class
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "feature.h"
#include "level.h"

class Mob;

/** Various hidden traps throughout the dungeon
 *  can trigger and endanger the player.
 */
class Trap : public Feature {
	public:
		/** Constructor.
		 * @param location Position of the trap
		 * @param type Type of trap (dart, teleport, pitfall, etc)
		 * @param visible Whether the trap is revealed
		 */
		Trap(Coord location, unsigned char type, bool visible);
		/** Trigger the trap on the given mob.
		 * Return the next level if a pitfall, otherwise
		 * return the given level.
		 */
		Level* activate(Mob*, Level*);

		/** Records how many type of traps there are for rand-gen purposes. */
		static constexpr unsigned int MAX_TYPE = 5;

		/** Creates/returns a random trap at the given coordinates. */
		static Trap* randomTrap(Coord);
	private:
		/** Type of the trap.
		   0 = Door Trap
		   1 = Arrow Trap
		   2 = Sleep Trap
		   3 = Bear Trap
		   4 = Teleport Trap
		   5 = Dart Trap
		*/
		unsigned char type;
};
