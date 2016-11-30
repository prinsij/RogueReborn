/**
 * @file uistate.h
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member declarations for the UIState class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"

/** Class modeling a state of the game interface.
 * Game transitions between these states like a
 * finite state machine.
 *
 * Environment variables: input device (e.g., keyboard) and output device (e.g., monitor)
 */
class UIState {
	public:
		UIState();
		/** Render the current UI */
		virtual void draw(TCODConsole*);
		/** Do whatever is needed in response to keypresses
		 *  then return state to transition to (can be self).
		 */
		virtual UIState* handleInput(TCOD_key_t);
		/** Destructor */
		virtual ~UIState();
};
