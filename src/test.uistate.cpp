/**
 * @file test.uistate.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <typeinfo>

#include "include/coord.h"
#include "include/invscreen.h"
#include "include/playstate.h"
#include "libtcod/include/libtcod.hpp"
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
			auto ps = new PlayState(player, level);
			auto key = TCOD_key_t();
			key.c = 'i';
			std::cerr << key.c << "\n";
			std::cerr << (player->hasCondition(PlayerChar::SLEEPING) == true) << "\n";
			auto iscreen = ps->handleInput(key);
			std::cerr << typeid(iscreen).name() << "\n";
			assert(dynamic_cast<InvScreen*>(iscreen) != NULL, "i key should open inventory");
			key = TCOD_key_t();
			key.vk = TCODK_ESCAPE;
			assert(dynamic_cast<PlayState*>(ps->handleInput(key)) != NULL, "escape key should exit inventory");
			key = TCOD_key_t();
			key.c = 'y';
			ps->handleInput(key);
			std::cerr << player->getLocation().toString() << "\n";
			assert(player->getLocation() == Coord(9,9), "movement should place player in correct location");

			comment("Finished UIState tests.");
		}
};
