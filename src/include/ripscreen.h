/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: ripscreen.h
 */ 

#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "../libtcod/include/libtcod.hpp"
#include "level.h"
#include "playerchar.h"
#include "uistate.h"

struct ScoreItem;

class RIPScreen : public UIState {
	public:
		RIPScreen(PlayerChar*, Level*, std::string);
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		std::vector<ScoreItem> scores;
		const std::string SCORE_FILE = "scores.txt";
};