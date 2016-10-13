#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"

UIState::UIState() {}

void UIState::draw(TCODConsole* con) {}

UIState* UIState::handleInput(TCOD_key_t key) {
	return new UIState();
}

UIState::~UIState() {}
