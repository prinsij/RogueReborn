/**
 * @file test.uistate.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>

#include "include/coord.h"
#include "include/controls.h"
#include "include/invscreen.h"
#include "include/statusscreen.h"
#include "include/playstate.h"
#include "libtcod/include/libtcod.hpp"
#include "include/wand.h"
#include "test.testable.h"

class UIStateTest : public Testable {
	public:
		UIStateTest() {};

		void test() {
			comment("Testing UIState");

			auto player = new PlayerChar(Coord(10, 10), "Test Char");
			auto level = new Level(1, player);
			level->registerMob(player);
			level->clear();
			UIState* ps = new PlayState(player, level);
			auto key = TCOD_key_t();
			key.c = KEYS::INV;
			auto iscreen = ps->handleInput(key);
			assert(dynamic_cast<InvScreen*>(iscreen) != NULL, "The 'i' key should open inventory");
			key = TCOD_key_t();
			key.vk = TCODK_ESCAPE;
			assert(dynamic_cast<PlayState*>(ps->handleInput(key)) != NULL, "Escape key should exit inventory");

			key = TCOD_key_t();
			key.c = 'y';
			ps->handleInput(key);
			assert(player->getLocation() == Coord(9,9), "Movement should place player in correct location");
			
			key = TCOD_key_t();
			key.c = KEYS::INFO;
			auto sscreen = ps->handleInput(key);
			assert(dynamic_cast<StatusScreen*>(sscreen) != NULL, "The 'c' key should open status screen");
			key = TCOD_key_t();
			key.vk = TCODK_ESCAPE;
			ps = sscreen->handleInput(key);
			assert(dynamic_cast<PlayState*>(ps) != NULL, "Escape key should exit status screen");
			
			key = TCOD_key_t();
			key.c = KEYS::ZAP;
			ps->handleInput(key);
			key = TCOD_key_t();
			key.vk = TCODK_LEFT;
			assert(ps->handleInput(key) == ps, "Pressing zap button with no wand should do nothing");
			auto wand = new Wand(Coord(0,0));
			player->getInventory().add(*wand);
			key = TCOD_key_t();
			key.c = KEYS::ZAP;
			ps = ps->handleInput(key);
			key = TCOD_key_t();
			key.vk = TCODK_LEFT;
			auto zscreen = ps->handleInput(key);
			assert(dynamic_cast<InvScreen*>(zscreen) != NULL, "Zap button with wand should open dir prompt then inventory");

			comment("Finished UIState tests.");
		}
};
