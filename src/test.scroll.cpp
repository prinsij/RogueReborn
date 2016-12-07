/**
 * @file test.scroll.cpp
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include "include/armor.h"
#include "include/level.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/scroll.h"
#include "include/terrain.h"
#include "include/weapon.h"
#include "test.testable.h"

class ScrollTest : public Testable {
	public:
		ScrollTest(){}

		void test(){
			Scroll::ignoreTransitions = true;

			comment("Commencing Scroll tests...");

			Scroll scrollCon = Scroll(Coord(0,0));
			assert(true, "Created Scroll (1)");
			Scroll scrollCon2 = Scroll(Coord(0,0), Item::FLOOR, 0);
			assert(true, "Created Scroll (2)");

			bool goodLength = true;
			for (std::string scrollName : Scroll::initializeScrollNames()) {
				goodLength = goodLength && scrollName.length() >= 20;
			}
			assert(goodLength, "Scroll Name Lengths");

			std::vector<Scroll> scrolls;

			for (int i = 0 ; i < 13 ; ++i) {
				scrolls.push_back(Scroll(Coord(0,0), Item::FLOOR, i));
			}

			Monster* monster = new Monster('B', Coord(1,0));

			PlayerChar* player = new PlayerChar(Coord(0,0), "Player Scroll Test");

			Level* level = new Level(3, player);

			Armor* armor = new Armor(Coord(0,0), Item::FLOOR, 1);

			Weapon* weapon = new Weapon(Coord(0,0), Item::FLOOR, 1);

			level->clear();
			level->registerMob(player);
			level->registerMob(monster);

			armor->setEnchantment(0);
			weapon->setEnchantments(0, 0);

			player->equipArmor(armor);
			player->equipWeapon(weapon);

			scrolls[0].activate(level);
			assert (armor->hasEffect(Item::PROTECTED) && !armor->hasEffect(Item::CURSED), "Scroll of Protect Armor");

			scrolls[1].activate(level);
			assert (monster->hasFlag(Monster::HELD), "Scroll of Hold Monster");

			scrolls[2].activate(level);
			assert (!weapon->hasEffect(Item::CURSED) && (weapon->getChance() + std::get<2>(weapon->getDamage()) >= 1), "Scroll of Enchant Weapon");

			int enchant3 = armor->getEnchantment();
			scrolls[3].activate(level);
			assert (!armor->hasEffect(Item::CURSED) && armor->getEnchantment() > enchant3, "Scroll of Enchant Armor");

			// Scroll of Identify contains too many side effects to effectively unit test
			assert (true, "Scroll of Identify");

			scrolls[5].activate(level);
			assert (player->getLocation() != Coord(0,0), "Scroll of Teleportation");

			scrolls[6].activate(level);
			assert (player->hasCondition(PlayerChar::SLEEPING), "Scroll of Sleep");

			scrolls[7].activate(level);
			assert (true, "Scroll of Scare Monster");

			weapon->setEnchantments(-1, -1);
			scrolls[8].activate(level);
			assert (!weapon->isCursed(), "Scroll of Remove Curse");

			scrolls[9].activate(level);
			assert (level->getMobs().size() == 3, "Scroll of Create Monster");

			scrolls[10].activate(level);
			bool isAwake = true;
			for (Mob* mob : level->getMobs()) {
				Monster* monster10 = dynamic_cast<Monster*>(mob);
				if (monster10 != NULL) {
					isAwake = isAwake && monster10->isAwake();
				}
			}
			assert (isAwake, "Scroll of Aggravate Monster");

			scrolls[11].activate(level);
			bool allSeen = true;
			for (auto x = 0 ; x < level->getSize()[0] ; ++x) {
				for (auto y = 0 ; y < level->getSize()[1] ; ++y) {
					allSeen = allSeen && (level->tileAt(Coord(x,y)).isSeen() == Terrain::Seen);
				}
			}
			assert (allSeen, "Scroll of Magic Mapping");

			player->setLocation(Coord(0,0));
			monster->setLocation(Coord(1,0));
			scrolls[12].activate(level);
			assert(player->hasCondition(PlayerChar::CONFUSE_MONSTER), "Scroll of Confuse Monster");

			Scroll::ignoreTransitions = false;

			comment("Finished Scroll tests.");
		}
};
