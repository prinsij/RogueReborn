/**
 * @file ripscreen.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the RIPScreen class
 */ 

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "include/debug.h"
#include "include/globals.h"
#include "include/playerchar.h"
#include "include/random.h"
#include "include/ripscreen.h"
#include "libtcod/include/libtcod.hpp"

struct ScoreItem {
	ScoreItem(int gold, int depth, std::string name, std::string death)
		: gold(gold)
		, depth(depth)
		, name(name)
		, death(death)
	{}
	int gold, depth;
	std::string name, death;
	static const char DELIM = ',';
	static ScoreItem decode(std::string line) {
		std::stringstream ss(line);
		std::string temp;

		if (!readItem(ss, temp))
			throw std::invalid_argument("bad format");
		int gold = std::stoi(temp);
		if (!readItem(ss, temp))
			throw std::invalid_argument("bad format");
		int depth = std::stoi(temp);
		if (!readItem(ss, temp))
			throw std::invalid_argument("bad format");
		std::string name = temp;
		if (!readItem(ss, temp))
			throw std::invalid_argument("bad format");

		std::string death = temp;
		return ScoreItem(gold, depth, name, death);
	}

	std::string encode() {
		return std::to_string(gold) + DELIM
			+  std::to_string(depth) + DELIM
			+  name + DELIM + death;
	}

	static bool readItem(std::stringstream& ss, std::string& str) {
		if (!std::getline(ss, str, DELIM)) {
#ifdef DEBUG
			std::cerr << "error parsing score file\n";
#endif
			return false;
		}
		return true;
	}

	bool operator<(const ScoreItem& other) const {
		return gold < other.gold;
	}
};


RIPScreen::RIPScreen(PlayerChar* player,
					 Level* level, std::string reason)
	: player(player)
	, wasVictory(reason == VICTORY_STR)
{

	std::ifstream scoreFile(SCORE_FILE);
	std::string line;
	if (scoreFile.is_open()) {
		while (std::getline(scoreFile, line)) {
			try {
				scores.push_back(ScoreItem::decode(line));
			} catch (const std::exception& e) {
#ifdef DEBUG
				std::cerr << "Error: " << e.what() << " while reading " << SCORE_FILE << "\n";
#endif
			}
		}
		scoreFile.close();
	} else {
#ifdef DEBUG
		std::cerr << "could not open " << SCORE_FILE << "\n";
#endif
	}
	scores.push_back(ScoreItem(player->getGold()+1000*(int)wasVictory, level->getDepth(), player->getName(), reason));
	// create if not exist, otherwise append
	std::ofstream outStream(SCORE_FILE, std::ios::app | std::ios::out);
	if (outStream.is_open()) {
		outStream << scores.back().encode() << "\n";
	}
	outStream.close();
	delete level;
	std::sort(scores.begin(), scores.end());
	std::reverse(scores.begin(), scores.end());

	leaves = "";
	flowers = "";

	// Leaves
	for (int x = 40 - GRAVE_WIDTH/2 - 2 ; x <= 40 + GRAVE_WIDTH/2 + 2 ; x ++) {
		int rng = Generator::intFromRange(0, 5);
		std::string symbol = "";
		if (rng == 0) symbol = ")";
		else if (rng == 1) symbol = "(";
		else if (rng == 2) symbol = "/";
		else if (rng == 3) symbol = "\\";
		else symbol = "+";

		leaves += symbol;
	}

	// Flowers
	for (int x = 40 - GRAVE_WIDTH/2 - 2 ; x <= 40 + GRAVE_WIDTH/2 + 2 ; x ++) {
		if (Generator::randPercent() <= 15) {
			flowers += "*";
		} else {
			flowers += " ";
		}
	}

}

void RIPScreen::draw(TCODConsole* con) {
	if (!wasVictory) {
		int leafCol = 40 - GRAVE_WIDTH/2 - 2;
		int flowerCol = 40 - GRAVE_WIDTH/2 - 2;
		int leafRow = 13;
		int flowerRow = 12;

		con->print(leafCol, leafRow, leaves.c_str());
		con->print(flowerCol, flowerRow, flowers.c_str());

		for (int col = leafCol ; col < static_cast<int>(leafCol + leaves.length()) ; col++) {
			con->setCharForeground(col, leafRow, TCODColor::green);
		}

		for (int col = flowerCol ; col < static_cast<int>(flowerCol + flowers.length()) ; col++) {
			con->setCharForeground(col, flowerRow, TCODColor::red);
		}

		// Top
		for (int x = 40 - GRAVE_WIDTH/2 + 2 ; x <= 40 + GRAVE_WIDTH/2 - 2 ; x ++) {
			con->print(x, 1, "_");
			con->setCharForeground(x, 1, TCODColor::lightGrey);
		}

		// Diagonal
		for (int x = 0 ; x < 3 ; x ++) {
			con->print(40 - GRAVE_WIDTH/2 + 1 - x, x + 2, "/");
			con->print(40 + GRAVE_WIDTH/2 - 1 + x, x + 2, "\\");
			con->setCharForeground(40 - GRAVE_WIDTH/2 + 1 - x, x + 2, TCODColor::lightGrey);
			con->setCharForeground(40 + GRAVE_WIDTH/2 - 1 + x, x + 2, TCODColor::lightGrey);
		}

		// Sides
		for (int i = 5 ; i < 13 ; i ++) {
			con->print(40 - GRAVE_WIDTH/2 - 1, i, "|");
			con->print(40 + GRAVE_WIDTH/2 + 1, i, "|");
			con->setCharForeground(40 - GRAVE_WIDTH/2 - 1, i, TCODColor::lightGrey);
			con->setCharForeground(40 + GRAVE_WIDTH/2 + 1, i, TCODColor::lightGrey);
		}

		// Bottom
		for (int x = 0 ; x < 10 ; x ++) {
			con->print(40 - GRAVE_WIDTH/2 - 3 - x, 13, "_");
			con->print(40 + GRAVE_WIDTH/2 + 3 + x, 13, "_");
			con->setCharForeground(40 - GRAVE_WIDTH/2 - 3 - x, 13, TCODColor::lightGrey);
			con->setCharForeground(40 + GRAVE_WIDTH/2 + 3 + x, 13, TCODColor::lightGrey);
		}

		std::string name = player->getName();
		if (static_cast<int>(name.length()) > GRAVE_WIDTH - 1) {
			name = name.substr(0, GRAVE_WIDTH - 4) + "...";
		}

		con->print(39, 3, "RIP");
		con->print(40 - name.length()/2, 6, name.c_str());
	}

	int y = 16;
	int maxY = 16 + 2*10;
	int x = con->getWidth()/4;
	for (ScoreItem item : scores) {
		con->printEx(x, y, TCOD_BKGND_DEFAULT, TCOD_RIGHT, (std::to_string(item.gold) + ": ").c_str());
		con->printEx(x + 1, y, TCOD_BKGND_DEFAULT, TCOD_LEFT, (item.name + " " + item.death + " on level " + std::to_string(item.depth)).c_str());

		for (int col = x ; col >= static_cast<int>(std::to_string(item.gold).length() + 2) ; col--) {
			con->setCharForeground(col, y, TCODColor::yellow);
		}

		y += 2;

		if (y == maxY) break;
	}

	if (wasVictory) {
		con->printEx(SCREEN_WIDTH/2, 8, TCOD_BKGND_DEFAULT, TCOD_CENTER, "You Win!");
	}
}

UIState* RIPScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE || key.vk == TCODK_SPACE || key.vk == TCODK_ENTER) {
		delete player;
		player = NULL;
		return NULL;
	}
	return this;
}
