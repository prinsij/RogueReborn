/**
 * @file mastercontroller.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the MasterController class
 */ 

#pragma once

#include "../libtcod/include/libtcod.hpp"
#include "uistate.h"

/** Controls the top level flow flow of the
 *  application and main game loop.
 *  Called directly from main.
 */
class MasterController {
	public:
		/** All game logic is inside, so no params
		 *  needed for constructor
		 */
		MasterController();
		/** Main game loop.
		 * Treats the game as a state machine, where each
		 * state is UIState. First calls the draw() method
		 * on the current state, then the handleInput() method,
		 * from which it retrieves the next state. If the next state
		 * is different, it deletes the current and swaps it
		 * out. This loop repeats for each frame of the game.
		 */
		void run();
	private:
		/** Current interface state */
		UIState* currState;
		/** Max number of frames per second */
		const int FPS_LIMIT = 60;
		/** Key to toggle fullscreen. */
		static constexpr char FULLSCREEN_TOGGLE = '~';
};
