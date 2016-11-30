/**
 * @file saving.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>

#include "include/armor.h"
#include "include/coord.h"
#include "include/debug.h"
#include "include/item.h"
#include "include/level.h"
#include "include/playerchar.h"
#include "include/saving.h"
#include "include/weapon.h"

using namespace std;

string encode(PlayerChar* player, Level* level) {
	string c = ",";
	string result = "";
	result += to_string(player->gold)
		+ c + to_string(player->foodLife)
		+ c + to_string(player->dexterity)
		+ c + to_string(player->currentStr)
		+ c + to_string(player->maxStr)
		+ c + to_string(player->moves)
		+ c + to_string(player->oocTurns)
		+ c + to_string(player->armor)
		+ c + to_string(player->currentHP)
		+ c + to_string(player->maxHP)
		+ c + to_string(player->exp)
		+ c + to_string(player->level)
		+ c + player->name
		+ c + to_string(level->getDepth());
	string weap = "-1,-1,-1";
	if (player->getWeapon() != NULL) {
		weap = to_string(player->getWeapon()->type);
		weap += c + to_string(player->getWeapon()->enchantHit);
		weap += c + to_string(player->getWeapon()->enchantDamage);
	}
	result += c + weap;
	string armor = "-1,-1";
	if (player->getArmor() != NULL) {
		armor = to_string(player->getArmor()->type);
		armor += c + to_string(player->getArmor()->enchantProtection);
	}
	result += c + armor;
	return result;
}

tuple<PlayerChar*, Level*> decode(string encoding) {
	vector<string> cells;
	string segment;
	stringstream ss;
	ss << encoding;
	while (getline(ss, segment, ',')) {
		cells.push_back(segment);
	}
#ifdef DEBUG
	for (auto i : cells) {
		cout << '\t' << i << "\n";
	}
#endif
	auto player = new PlayerChar(Coord(0,0), "jacoby");
	player->gold = stoi(cells[0]);
	player->foodLife = stoi(cells[1]);
	player->dexterity = stoi(cells[2]);
	player->currentStr = stoi(cells[3]);
	player->maxStr = stoi(cells[4]);
	player->moves = stoi(cells[5]);
	player->oocTurns = stoi(cells[6]);
	player->armor = stoi(cells[7]);
	player->currentHP = stoi(cells[8]);
	player->maxHP = stoi(cells[9]);
	player->exp = stoi(cells[10]);
	player->level = stoi(cells[11]);
	player->name = cells[12];
	auto level = new Level(stoi(cells[13]), player);
	level->registerMob(player);
	level->generate();
	int weaptype = stoi(cells[14]);
	if (weaptype != -1) {
		player->itemWeapon = new Weapon(Coord(0,0), Item::INVENTORY, weaptype);
		player->itemWeapon->setEnchantments(stoi(cells[15]), stoi(cells[16]));
	}
	int armortype = stoi(cells[17]);
	if (armortype != -1) {
		player->itemArmor = new Armor(Coord(0,0), Item::INVENTORY, armortype);
		player->itemArmor->setEnchantment(stoi(cells[18]));
	}
	return tuple<PlayerChar*, Level*>(player, level);
}
