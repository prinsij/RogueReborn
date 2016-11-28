/**
 * @file statusscreen.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member definitions for the StatusScreen class
 */ 

#include <string>

#include "include/armor.h"
#include "include/playerchar.h"
#include "include/playstate.h"
#include "include/statusscreen.h"
#include "include/weapon.h"

StatusScreen::StatusScreen(PlayerChar* pc, Level* lvl)
	: player(pc)
	, level(lvl)
{}

void StatusScreen::draw(TCODConsole* con) {
	con->print(1, 1, ("Rogue:  " + player->getName()).c_str());
	auto weap = player->getWeapon() != NULL ? player->getWeapon()->getDisplayName() : "None";
	con->print(1, 3, ("Weapon: " + weap).c_str());
	auto armor = player->getArmor() != NULL ? player->getArmor()->getDisplayName() : "None";
	con->print(1, 5, ("Armor:  " + armor).c_str());

	con->print(1, 7, ("Depth:  " + std::to_string(level->getDepth())).c_str());

	std::string amulet = player->hasAmulet() ? "Yes" : "No";
	con->print(1, 9, ("Amulet: " + amulet).c_str());
}

UIState* StatusScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_SPACE || key.vk == TCODK_ESCAPE) {
		return new PlayState(player, level);
	}
	return this;
}
