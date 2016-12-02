/**
 * @file helpscreen.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Member definitions for the HelpScreen class
 */ 

#include "include/controls.h"
#include "include/helpscreen.h"
#include "include/playstate.h"

const char HelpScreen::hotkeys[] = {KEYS::REST, KEYS::SYMBOLS, KEYS::ASCEND, KEYS::DESCEND,
								 KEYS::HELP, KEYS::PUT, KEYS::QUIT, KEYS::REMOVE, KEYS::TAKEOFF, KEYS::WEAR,
								 KEYS::DROP, KEYS::EAT, KEYS::INV, KEYS::LOG, KEYS::QUAFF, KEYS::READ, KEYS::SEARCH,
								 KEYS::THROW, KEYS::WIELD, KEYS::STOW, KEYS::ZAP, KEYS::TOGGLE_SAVE, KEYS::INFO};

const std::string HelpScreen::descs[] = {"Rest", "List symbols", "Ascend stairs", "Descend stairs",
						   "List commands", "<obj> <hand> Put on ring", "Quit (give up)",
						   "<hand> Remove ring", "Take off armor", "<obj> Wear armor",
						   "<obj> Drop object", "<obj> Eat food", "Inventory", "View previous log",
						   "<obj> Quaff potion", "<obj> Read scroll", "Search for trap or door",
						   "<dir> <obj> Throw object", "<obj> Wield weapon", "Stow Weapon",
						   "<dir> <obj> Zap wand", "Toggle save", "Character Info"};

HelpScreen::HelpScreen(PlayerChar* pc, Level* lvl)
	: player(pc)
	, level(lvl)
{}

void HelpScreen::draw(TCODConsole* con) {
	con->print(1, 1, "y k u");
	con->print(2, 2, "\\|/");
	con->print(1, 3, "h-*-l");
	con->print(1, 4, " /|\\");
	con->print(1, 5, "b j n");

	for (int row = 1 ; row <= 5 ; row++) {
		for (int col = 0 ; col <= 5 ; col ++) {
			con->setCharForeground(col, row, TCODColor::green);
		}
	}

	/*
	con->print(9, 0, "Shift <dir> Move until stopped");
	con->print(9, 1, " Ctrl <dir> \" until near");
	con->print(9, 2, "    g <dir> \" with no pickup");
	*/

	int i = 0;
	for (int y = 0; y < 13; y++) {
		const char c_str[2] = {hotkeys[i], '\0'};
		con->print(1, 8 + 2*y, c_str);
		con->print(6, 8 + 2*y, descs[i].c_str());
		i += 1;

		con->setCharForeground(1, 8 + 2*y, TCODColor::cyan);
	}

	for (int y = 13; y < 23 && (unsigned int) i < sizeof(hotkeys)/sizeof(*hotkeys); y++) {
		const char c_str[2] = {hotkeys[i], '\0'};
		con->print(41, 8 + 2*(y - 13), c_str);
		con->print(46, 8 + 2*(y - 13), descs[i].c_str());
		i += 1;

		con->setCharForeground(41, 8 + 2*(y - 13), TCODColor::cyan);
	}
}

UIState* HelpScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE || key.vk == TCODK_SPACE) {
		return new PlayState(player, level);
	}
	return this;
}
