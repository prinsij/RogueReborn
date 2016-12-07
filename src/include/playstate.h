/**
 * @file playstate.h
 * @author Team Rogue++
 * @date December 07, 2016
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
							  HELPLESS_MSG = "You are helpless (press SPACE to continue",
							  DROP_PROMPT = "Choose an item to drop",
							  NO_QUAFF_MSG = "You have nothing you can quaff",
							  QUAFF_PROMPT = "Choose a potion to quaff",
							  NO_READ_MSG = "You have nothing you can read",
							  READ_PROMPT = "Choose a scroll to read",
							  ALREADY_WIELD = "You are already wielding something",
							  WIELD_PROMPT = "Choose a weapon to wield",
							  NO_WIELD_MSG = "You have nothing you can wield",
							  ALREADY_WEAR = "You are already wearing something",
							  WEAR_PROMPT = "Choose a piece of armor to wear",
							  NO_WEAR_MSG = "You have nothing you can wear",
							  NO_TAKE_OFF_MSG = "You are not wearing anything",
							  NO_REMOVE_MSG = "You are not wearing any rings",
							  FINGER_DEFICIT = "You have no more fingers",
							  NO_PUT_MSG = "You have nothing to put on your finger(s)",
							  PUT_PROMPT = "Choose a ring to put on your finger",
							  NO_STOW_MSG = "You are not wielding anything",
							  THROW_PROMPT = "Choose an item to throw",
							  NO_THROW_MSG = "You have nothing you can throw",
							  ZAP_PROMPT = "Choose a wand to zap with",
							  NO_ZAP_MSG = "You have nothing with which to zap",
							  EAT_PROMPT = "Choose a piece of food to eat",
							  NO_EAT_MSG = "You have nothing to eat",
							  NO_ASCEND_MSG = "Some magical force prevents your passage upward.",
							  OPEN_DOOR_MSG = "You open the door",
							  CLOSE_DOOR_MSG = "You close the door",
							  TIGHTEN_FINGER = " tightens its grip on your finger",
							  LOOSEN_GRIP = "You cannot loosen your grip on the ",
							  REST_MSG = "You rest briefly",
							  SEARCH_MSG = "You search your surroundings for secrets",
							  SECRET_MSG = "You uncover a secret",
							  SAVE_ON_MSG = "You will save at the end of the this level",
							  SAVE_OFF_MSG = "You won't save at the end of the this level",
							  NO_DROP_MSG = "You have nothing to drop",
							  ALREADY_THERE_MSG = "There is already something there";

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

		/** Occurs when the player attempts to wear a piece of armor. */
		UIState* attemptWear(int);

		/** Occurs when the player attempts to wield a weapon. */
		UIState* attemptWield(int);

		/** Occurs when the player attempts to remove a ring. */
		UIState* attemptRemove(int);

		/** Occurs when the player attempts to take off armor. */
		UIState* attemptTakeOff(int);

		/** Toggles the flag that determines if the player will
		 *  be directed to the save screen after the level.
		 */
		UIState* toggleSaveFlag();

		/** Occurs when the player attempts to drop an item from
		 *  their inventory.
		 */
		UIState* attemptDrop(int);

		/** Occurs when the player attempts to quaff a potion. */
		UIState* attemptQuaff(int);

		/** Occurs when the player is in debug mode. */
		void handleWizardry(TCOD_key_t);

		/** Occurs when the player searches their surroundings
		 *  for hidden secrets.
		 */
		UIState* attemptSearch(int);

		/** Occurs when the player uses the movement keys, including
		 *  when they use them to attack.
		 */
		UIState* attemptMove(Coord, TCOD_key_t, int);

		/** Occurs when the player attempts to climb stairs. */
		UIState* attemptClimb(bool);

		/** Occurs when the player attempts to eat a piece of food. */
		UIState* attemptEat(int);

		/** Occurs when the player attempts to zap with a wand. */
		UIState* attemptZap(int);

		/** Occurs when the player attempts to throw an item. */
		UIState* attemptThrow(int);

		/** Occurs when the player attempts to stow their weapon. */
		UIState* attemptStow(int);

		/** Occurs when the player attempts to read a scroll. */
		UIState* attemptRead(int);

		/** Occurs when the player attempts to put on a ring. */
		UIState* attemptPutOn(int);
};
