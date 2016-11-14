/**
 * @file helpscreen.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the HelpScreen class
 */ 

#include "include/helpscreen.h"
#include "include/playstate.h"

HelpScreen::HelpScreen(PlayerChar* pc, Level* lvl)
	: player(pc)
	, level(lvl)
{}

void HelpScreen::draw(TCODConsole* con) {
	con->print(0, 0, "y k u");
	con->print(0, 1, "\\|/");
	con->print(0, 2, "h-*-l");
	con->print(0, 3, " /|\\");
	con->print(0, 4, "b j n");

	/*
	con->print(9, 0, "Shift <dir> Move until stopped");
	con->print(9, 1, " Ctrl <dir> \" until near");
	con->print(9, 2, "    g <dir> \" with no pickup");
	*/

	std::string hotkeys[] = {".", "/", "<", ">",
							 "?", "P", "Q", "R", "T", "W",
							 "d", "e", "i", "o", "q", "r", "s", "t",
							 "w", "S", "Z"};
	std::string descs[] = {"Rest", "List symbols", "Ascend stairs", "Descend stairs",
						   "List commands", "<obj> <hand> Put on ring", "Quit (give up)",
						   "<hand> Remove ring", "Take off armor", "<obj> Wear armor",
						   "<obj> Drop object", "<obj> Eat food", "Inventory", "View previous log",
						   "<obj> Quaff potion", "<obj> Read scroll", "Search for trap or door",
						   "<dir> <obj> Throw object", "<obj> Wield weapon", "Stow Weapon",
						   "<dir> <obj> Zap wand"};
	int i = 0;
	for (int y=6; y < 20; y++) {
		con->print(0, y, hotkeys[i].c_str());
		con->print(9, y, descs[i].c_str());
		i += 1;
	}
	for (int y=0; y < 23 && (unsigned int) i < sizeof(hotkeys)/sizeof(*hotkeys); y++) {
		con->print(41, y, hotkeys[i].c_str());
		con->print(46, y, descs[i].c_str());
		i += 1;
	}
}

UIState* HelpScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE || key.vk == TCODK_SPACE) {
		return new PlayState(player, level);
	}
	return this;
}
