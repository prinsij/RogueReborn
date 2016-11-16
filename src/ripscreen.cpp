/**
 * @file ripscreen.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the RIPScreen class
 */ 

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "include/playerchar.h"
#include "include/ripscreen.h"
#include "include/globals.h"
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
			std::cerr << "error parsing score file\n";
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
			} catch (std::string param) {
				std::cerr << param << " while reading " << SCORE_FILE << "\n";
			}
		}
		scoreFile.close();
	} else {
		std::cerr << "could not open " << SCORE_FILE << "\n";
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
}

void RIPScreen::draw(TCODConsole* con) {
	int y = 3;
	int x = con->getWidth()/2;
	for (ScoreItem item : scores) {
		con->printEx(x, y, TCOD_BKGND_DEFAULT, TCOD_CENTER, (std::to_string(item.gold) + ":" + item.name + " " + item.death
					+ " on level " + std::to_string(item.depth)).c_str());
		y += 2;
	}
	if (wasVictory) {
		con->printEx(x, 1, TCOD_BKGND_DEFAULT, TCOD_CENTER, "You Win!");
	} else {
		con->printEx(x, 1, TCOD_BKGND_DEFAULT, TCOD_CENTER, std::string("RIP").c_str());
	}
}

UIState* RIPScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		delete player;
		player = NULL;
		return NULL;
	}
	return this;
}
