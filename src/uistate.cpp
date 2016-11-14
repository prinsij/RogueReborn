/**
 * @file uistate.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the UIState class
 */ 

#include "include/uistate.h"
#include "libtcod/include/libtcod.hpp"

UIState::UIState() {}

void UIState::draw(TCODConsole* con) {}

UIState* UIState::handleInput(TCOD_key_t key) {
	return this;
}

UIState::~UIState() {}