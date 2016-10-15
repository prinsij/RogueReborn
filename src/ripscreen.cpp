#include "include/ripscreen.h"
#include "include/playerchar.h"
#include "libtcod/include/libtcod.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

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
};


RIPScreen::RIPScreen(PlayerChar* player)
	: player(player)
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
	scores.push_back(ScoreItem(player->getGold(), -1, player->getName(), "unknown"));
	// create if not exist, otherwise append
	std::ofstream outStream(SCORE_FILE, std::ios::app | std::ios::out);
	if (outStream.is_open()) {
		outStream << scores.back().encode() << "\n";
	}
	outStream.close();
}

void RIPScreen::draw(TCODConsole* con) {
	int i = 0;
	for (ScoreItem item : scores) {
		con->print(0, i, (std::to_string(item.gold) + ":" + item.name + " " + item.death 
					+ " on level " + std::to_string(item.depth)).c_str());
		i++;
	}
	con->print(10, 10, std::string("rip").c_str());
}

UIState* RIPScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		delete player;
		player = NULL;
		return NULL;
	}
	return this;
}
