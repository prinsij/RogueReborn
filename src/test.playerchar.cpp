/**
 * @file test.playerchar.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/armor.h"
#include "include/playerchar.h"
#include "include/random.h"
#include "include/weapon.h"
#include "test.testable.h"

class PlayerCharTest : public Testable {
	public:
		PlayerCharTest(){}

		const int RANDOM_TEST_COUNT = 5;

		void test(){

			comment("Testing PlayerChar!");

			Coord pos  = Coord(0,0);
			PlayerChar player = PlayerChar(pos, "test");

			assert(!player.hasAmulet(), "Player does not start with amulet");
			assert(player.getHP() == player.getMaxHP(), "Player starts at max HP");

			int a = player.getLevel();
			player.addExp(15);
			int b = player.getLevel();

			assert(b > a, "Level up by xp works");

			player.raiseLevel();
			a = player.getLevel();

			assert(a > b, "Level up by code hax works");

			for (auto i = 0; i < 5; i++){

				a = player.getHP();
				player.hit(1);
				b = player.getHP();

				assert(b < a, "Taking damage works");
			}

			//Weapon
			assert(player.calculateDamage() == 0, "Player cannot inflict damage with no weapon");

			Weapon w = Weapon(pos, Item::INVENTORY, 5);
			player.equipWeapon(&w);

			assert(player.calculateDamage() > 0, "Player can inflict damage with weapon (" + w.getName() + ")");
			assert(player.removeWeapon(), "Player can remove weapon");
			assert(player.calculateDamage() == 0, "Player cannot inflict damage once weapon is removed");

			assert(!player.removeArmor(), "Player cannot remove armor that is not equipped");

			Armor ar = Armor(pos, Item::INVENTORY, 0);
			player.equipArmor(&ar);

			assert(player.removeArmor(), "Player can remove armor that is equipped");


		}
};
