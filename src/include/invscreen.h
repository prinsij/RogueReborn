/**
 * @file invscreen.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the InvScreen class
 */ 

#pragma once

#include <functional>

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "playstate.h"
#include "uistate.h"

/** Interface state for viewing the contents of
 *  the player inventory.
 *
 * Environment variables: input device (e.g., keyboard) and output device (e.g., monitor)
 */

class InvScreen : public UIState {
	public:
		typedef std::function<UIState*(Item*, PlayerChar*, Level*)> transFunc;
		typedef std::function<bool(Item*)> filtFunc;
		/** Constructor.
		 * We take the playerchar and level so
		 * we can restore them once gameplay
		 * resumes.
		 * Includes filter for inventory and function for desired return state.
		 */
		InvScreen(PlayerChar*, Level*, filtFunc, transFunc, bool, std::string prompt="");
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
		/** Filters the contents of inventory (eg only food).
		 * True means display, false means don't.
		 */
		filtFunc filter;
		/** Function returning state we should go to after player picks an item. */
		transFunc transition;
		/** indicates whether choice is mandatory. */
		bool escapeable;
		/** Indicates to the user why the inventory screen is open. */
		std::string prompt;
};
