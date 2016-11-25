/**
 * @file mainmenu.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member definitions for the MainMenu class
 */ 

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>

#include "include/food.h"
#include "include/globals.h"
#include "include/level.h"
#include "include/mainmenu.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/potion.h"
#include "include/saving.h"
#include "include/uistate.h"
#include "include/weapon.h"
#include "include/wizard.h"
#include "libtcod/include/libtcod.hpp"

MainMenu::MainMenu()
	: nameBuffer("")
{}

void MainMenu::draw(TCODConsole* con) {
	int WIDTH = 60;
	int startX = con->getWidth()/2 - WIDTH/2 - 4;

	int conY = 2;

	con->print(0, conY++, "        ____________________________________________________________          ");
	con->print(0, conY++, "      (@\\                                                           \\       ");
	con->print(0, conY++, "       ^ \\                                                           \\      ");
	con->print(0, conY++, "          \\                                                           \\      ");
	con->print(0, conY++, "           \\                                                           \\     ");
	con->print(0, conY++, "            )                                                           )     ");
	con->print(0, conY++, "           /                                                           /      ");
	con->print(0, conY++, "          /                                                           /       ");
	con->print(0, conY++, "         (                                                           (        ");
	con->print(0, conY++, "          \\                                                           \\     ");
	con->print(0, conY++, "           \\                                                           \\    ");
	con->print(0, conY++, "            \\                                                           \\   ");
	con->print(0, conY++, "           (@)___________________________________________________________)   ");

	for (int row = 0 ; row < conY ; row++) {
		for (int col = 0 ; col < 80 ; col++) {
			con->setCharForeground(col, row, TCODColor::amber);
		}
	}

	std::string strTop = "@-- Welcome to Rogue Reborn -->,";
	std::string strBot = "~ Rogue++ Productions ~";

	int startTop = startX + WIDTH/2 + 5 - strTop.length()/2;
	int startBot = startX + WIDTH/2 + 5 - strBot.length()/2; 
	int rowTop = 5;
	int rowBot = 10;

	con->print(startTop, rowTop, strTop.c_str());
	con->print(startBot, rowBot, strBot.c_str());

	for (int col = startTop ; col < static_cast<int>(startTop + strTop.length()) ; col++) {
		con->setCharForeground(col, rowTop, TCODColor::yellow);
	}

	for (int col = startTop ; col < static_cast<int>(startTop + strTop.length()) ; col++) {
		con->setCharForeground(col, rowBot, TCODColor::orange);
	}

	int promptRow = 18;
	std::string prompt = "Who dare enter the Dungeons of Doom? ";

	con->print(1, promptRow, (prompt + nameBuffer).c_str());

	for (int col = 1 ; col <= static_cast<int>(prompt.length()) ; col++) {
		con->setCharForeground(col, promptRow, TCODColor::red);
	}

	if (time(NULL) % 2 == 0) {
		con->print(prompt.length() + nameBuffer.length() + 1, 18, "_");
	}
}

UIState* MainMenu::handleInput(TCOD_key_t key) {
	if (!key.pressed) return this;
	// Chop off a character in response to backspaces
	if (key.vk == TCODK_BACKSPACE) {
		if (!nameBuffer.empty()) {
			nameBuffer.resize(nameBuffer.size()-1);
		}
	// If enter we generate the first level and start the game
	} else if (key.vk == TCODK_ENTER) {
		if (!key.shift) {
			PlayerChar* player = new PlayerChar(Coord(10, 10), nameBuffer);
			setupPlayer(player);
			Level* level = new Level(1, player);
			level->registerMob(player);
			level->generate();
			player->appendLog("Hello " + player->getName() + ". Welcome to the Dungeons of Doom. Type [?] for help.");
			return new PlayState(player, level);
		} else {
			std::ifstream savefile(nameBuffer);
			if (savefile.is_open()) {
				std::string line;
				std::getline(savefile, line);
				savefile.close();
				std::remove(nameBuffer.c_str());
				auto pair = decode(line);
				return new PlayState(std::get<0>(pair), std::get<1>(pair));
			} else {
				std::cout << "ERROR OPENING SAVEFILE\n";
				nameBuffer = "ERROR";
			}
		}
	} else if (key.c) {
		// Append to name if its a valid name character
		if (VALID_NAME.find(key.c) != std::string::npos && nameBuffer.size() < MAX_NAME_LEN) {
			nameBuffer = nameBuffer + key.c;
		}
	}
	return this;
}

void MainMenu::setupPlayer(PlayerChar* player) {
	Weapon* weapon = new Weapon(player->getLocation(), Item::Context::INVENTORY, 5);
	weapon->setEnchantments(1, 1);
	player->pickupItem(weapon);
	player->equipWeapon(weapon);
	player->getInventory().remove(weapon);
	player->pickupItem(new Food(Coord(0,0), Item::Context::INVENTORY));
	player->pickupItem(new Food(Coord(0,0), Item::Context::INVENTORY));
	player->pickupItem(new Potion(Coord(0,0)));
#ifdef URAWIZARD
	player->pickupItem(new Potion(Coord(0,0), Item::Context::INVENTORY, 7)); // halluc
#endif
}
