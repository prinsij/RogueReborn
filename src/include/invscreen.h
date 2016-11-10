/**
 * @file invscreen.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the InvScreen class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "playstate.h"
#include "uistate.h"

/** Interface state for viewing the contents of
 *  the player inventory.
 */

class InvScreen : public UIState {
	public:
		/** Constructor.
		 * We take the playerchar and level so
		 * we can restore them once gameplay
		 * resumes.
		 */
		InvScreen(PlayerChar*, Level*);
		/** Draw the inventory.
		 * Shows like-and-stackable items grouped.
		 * Makes sure to not reveal the true names
		 * of undiscovered items.
		 */
		void draw(TCODConsole*);
		/** Handle input (just the quit key). */
		UIState* handleInput(TCOD_key_t);
	private:
		/** Reference to player for when gameplay resumes. */
		PlayerChar* player;
		/** Reference to level for when gameplay resumes. */
		Level* level;
};