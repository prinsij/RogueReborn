/**
 * @file logscreen.h
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member declarations for the LogScreen class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

class PlayerChar;
class Level;

/**
 * Controls the display of the event log.
 *
 * Environment variables: input device (e.g., keyboard) and output device (e.g., monitor)
 */
class LogScreen : public UIState {
	public:
		/** Constructor, takes info so we can return to regular
		 *  gameplay with it later.
		 */
		LogScreen(PlayerChar*, Level*);
		/** Allow the player to leave the log screen. */
		virtual UIState* handleInput(TCOD_key_t);
		/** Render the previous log messages, up is more recent. */
		virtual void draw(TCODConsole*);
	private:
		/** Reference to player for when we leave the log. */
		PlayerChar* player;
		/** Reference to level for when we leave the log. */
		Level* level;
		/** Number of messages to show. */
		static const int NUM_MESSAGES = 30;
};
