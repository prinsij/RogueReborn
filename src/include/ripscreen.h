/**
 * @file ripscreen.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the RIPScreen class
 */ 

#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "uistate.h"

/** Items in the score table. */
struct ScoreItem;

/** Interface state for post-death/retirement,
 *  looking at the high-score table.
 *
 * Environment variables: input device (e.g., keyboard), monitor, and the file system
 */
class RIPScreen : public UIState {
	public:
		/** Constructor.
		 * @param cause Cause of death/retirement
		 * @param level Level on which player died/retired
		 */
		RIPScreen(PlayerChar*, Level* level, std::string cause);
		/** Render. */
		virtual void draw(TCODConsole*);
		/** Handle player key input. */
		virtual UIState* handleInput(TCOD_key_t);
	private:
		/** Width of grave */
		int GRAVE_WIDTH = 14;

		/** Leaves at bottom of grave */
		std::string leaves;

		/** Flowers at bottom of grave */
		std::string flowers;

		/** Reference to player. */
		PlayerChar* player;
		/** Vector of score table items read from file
		 *  plus 1 created by recent death/retirement.
		 */
		std::vector<ScoreItem> scores;
		/** Location of score record. */
		const std::string SCORE_FILE = "scores.txt";

		/** Indicates whether the player beat the game. */
		bool wasVictory;
};
