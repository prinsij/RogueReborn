#include "include/ripscreen.h"
#include "include/playerchar.h"
#include "libtcod/include/libtcod.hpp"
#include <string>

RIPScreen::RIPScreen(PlayerChar* player)
	: player(player)
{}

void RIPScreen::draw(TCODConsole* con) {
	con->print(10, 10, std::string("rip").c_str());
}
