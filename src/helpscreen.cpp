#include "include/helpscreen.h"

HelpScreen::HelpScreen(PlayerChar* pc, Level* lvl)
	: player(pc)
	, level(lvl)
{}

void HelpScreen::draw(TCODConsole con*) {
	con->print(0, 0, "y k u");
}

UIState* HelpScreen::handleInput(TCOD_key_t key) {
	if (key.vk == TCODK_ESCAPE) {
		return new PlayState(player, level);
	}
	return this;
}
