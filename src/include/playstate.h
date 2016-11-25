/**
 * @file playstate.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the PlayState class
 */ 

#pragma once

#include <functional>

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "uistate.h"

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
		/** Delete internal components. */
		virtual ~PlayState();
	protected:
		static const int PROMPTX = 0, PROMPTY = 1;
		/** reference to player character. */
		PlayerChar* player;
		/** Reference to current dungeon level. */
		Level* level;
		/** Log this to the player when they attempt 
		 *  an action and fail due to inventory capacity.
		 */
		static constexpr auto NO_SPACE_LOG = "You have no space in your inventory",
							  QUIT_PROMPT = "Do you wish to end your quest now (Yes/No) ?",
							  HAND_PROMPT = "Which ring to remove (R/L) ?",
							  DIRECTION_PROMPT = "Which direction?",
							  HELPLESS_MSG = "You are helpless (press SPACE to continue";

	private:
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

		/** Combines similar functionality for quaff,
		 *  read, etc.
		 */
		template<typename T>
		UIState* attemptUse(std::string, std::string, std::function<bool(Item*)>,
							std::function<UIState*(T*)>);

};
