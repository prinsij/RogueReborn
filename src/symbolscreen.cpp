/**
 * @file symbolscreen.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Member definitions for the SymbolScreen class
 */ 

#include <iostream>

#include "include/playstate.h"
#include "include/symbolscreen.h"
#include "libtcod/include/libtcod.hpp"

SymbolScreen::SymbolScreen(PlayerChar* pc, Level* lvl)
	: player(pc)
	, level(lvl)
{}

const std::string SymbolScreen::symbols[] = {"#", ".", "+", "^", "%%", "*", ":", "!", "?",
							 "/", "=", "$", ")", "]", "A-Z", "@"};

const std::string SymbolScreen::explanations[] = {"Wall", "Floor", "Door", "Trap", "Stairs", "Gold",
								"Food", "Potion", "Scroll", "Wand/Staff", "Ring",
								"Amulet", "Weapon", "Armor", "Monsters", "Hero"};

void SymbolScreen::draw(TCODConsole* con) {
	for (unsigned int i=0; i < sizeof(symbols)/sizeof(*symbols); ++i) {
		int y = 2*i+1;
		con->print(4, y, symbols[i].c_str());
		con->print(8, y, explanations[i].c_str());
	}
}

UIState* SymbolScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE || key.vk == TCODK_SPACE) {
		return new PlayState(player, level);
	}
	return this;
}
