/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: playstate.h
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "uistate.h"

class Prompt;

/** Primary interface state, showing level, player,
 *  monsters, etc.
 */
class PlayState : public UIState {
	public:
		/** Constructor. */
		PlayState(PlayerChar*, Level*);
		/** Render, drawing (in this order),
		 *  ui, tiles, features, mobs.
		 */
		virtual void draw(TCODConsole*);
		/** Handle the various controls. */
		virtual UIState* handleInput(TCOD_key_t);
		/** Delete internal components (prompt). */
		virtual ~PlayState();
	private:
		/** reference to player character. */
		PlayerChar* player;
		/** Reference to current dungeon level. */
		Level* level;
		/** Prompt being shown to the user.
		 * eg: "Do thing? (Y/N)"
		 */
		Prompt* prompt;
		/** Update the portion of the map which has
		 *  been seen, and return the room which the
		 *  player character is in, if any.
		 * @see currRoom
		 */
		Room* updateMap();
		/** Which room the player is currently in.
		 * @see updateMap
		*/
		Room* currRoom;
};
