/**
 * @file mainmenu.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the MainMenu class
 */ 

#include <iostream>

#include "include/globals.h"
#include "include/level.h"
#include "include/mainmenu.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/uistate.h"
#include "include/weapon.h"
#include "include/food.h"
#include "include/potion.h"
#include "libtcod/include/libtcod.hpp"

MainMenu::MainMenu()
	: nameBuffer("")
{}

void MainMenu::draw(TCODConsole* con) {
	con->print(0, 0, "welcome to Rogue Reborn!");
	con->print(0, 1, ("Rogue's Name? " + nameBuffer).c_str());
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

		PlayerChar* player = new PlayerChar(Coord(10, 10), nameBuffer);
		setupPlayer(player);
		Level* level = new Level(0, player);
		level->registerMob(player);
		level->generate();
		player->appendLog("Hello " + player->getName() + ". Welcome to the Dungeons of Doom. Type [?] for help.");
		return new PlayState(player, level);
	} else if (key.c) {
		// Append to name if its a valid name character
		if (VALID_NAME.find(key.c) != std::string::npos) {
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
}
