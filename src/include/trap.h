/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: trap.h
 */ 

#pragma once

#include <string>

#include "coord.h"
#include "feature.h"

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
		/** Trigger the trap on the given mob. */
		void activate(Mob*);
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
		/** Whether the trap is revealed. */
		bool visible;
};
