/**
 * @file test.uistate.cpp
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member definitions for the UIStateTest class
 */ 

#include <iostream>

#include "include/controls.h"
#include "include/coord.h"
#include "include/invscreen.h"
#include "include/playstate.h"
#include "include/ripscreen.h"
#include "include/statusscreen.h"
#include "include/wand.h"
#include "libtcod/include/libtcod.hpp"
#include "test.testable.h"

/**
 * @brief      Tests the UIState class.
 */
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
			key = TCOD_key_t();
			key.vk = TCODK_ESCAPE;
			ps = zscreen->handleInput(key);
			assert(dynamic_cast<PlayState*>(ps) != NULL, "Escape should exit wand prompt");

			key = TCOD_key_t();
			key.c = KEYS::ZAP;
			ps = ps->handleInput(key);
			key = TCOD_key_t();
			key.vk = TCODK_LEFT;
			ps = ps->handleInput(key);
			key = TCOD_key_t();
			auto charges = wand->getCharges();
			for (auto pair : player->getInventory().getContents()) {
				if (pair.second.front() == wand) {
					key.c = pair.first;
					goto found_item;
				}
			}
			key.c = 'z';
			found_item:;
			ps = ps->handleInput(key);
			ps = ps->handleInput(key);
			assert(dynamic_cast<PlayState*>(ps) != NULL, "Casting wand should bring us back to a playstate");
			assert(charges == 1 || wand->getCharges() == charges-1, "Casting wand should have reduced charges");

			player->getInventory().remove(wand);
			delete wand;

			key = TCOD_key_t();
			key.c = KEYS::QUIT;
			ps = ps->handleInput(key);
			key = TCOD_key_t();
			key.c = 'Y';
			auto ripscreen = ps->handleInput(key);
			assert(dynamic_cast<RIPScreen*>(ripscreen) != NULL, "Quiting should bring us to rip screen");

			comment("Finished UIState tests.");
		}
};
