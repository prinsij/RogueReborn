/**
 * @file test.playerchar.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */

#include <iostream>
#include <string>
#include <vector>

#include "test.testable.cpp"
#include "include/playerchar.h"
#include "include/random.h"

class PlayerCharTest : public Testable {
	public:
		PlayerCharTest(){}

		const int RANDOM_TEST_COUNT = 5;

		void test(){

			comment("Testing PlayerChar!");			

			Coord pos  = Coord(0,0);
			PlayerChar player = PlayerChar(pos, "test");

			int a = player.getLevel();
			player.addExp(15);
			int b = player.getLevel();

			assert(b > a, "Level up works");

			for (auto i = 0; i < 5; i++){

				a = player.getHP();
				player.hit(1);
				b = player.getHP();

				assert (b < a, "Taking damage works");	
			}
		}
};