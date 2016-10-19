#pragma once
#include "uistate.h"
#include "playerchar.h"
#include "../libtcod/include/libtcod.hpp"
#include <vector>
#include <string>
#include <sstream>

struct ScoreItem;

class RIPScreen : public UIState {
	public:
		RIPScreen(PlayerChar*);
		virtual void draw(TCODConsole*);
		virtual UIState* handleInput(TCOD_key_t);
	private:
		PlayerChar* player;
		std::vector<ScoreItem> scores;
		const std::string SCORE_FILE = "scores.txt";
};
