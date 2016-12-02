/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.amulet.cpp"
#include "test.armor.cpp"
#include "test.coord.cpp"
#include "test.feature.cpp"
#include "test.food.cpp"
#include "test.goldpile.cpp"
#include "test.item.cpp"
#include "test.itemzone.cpp"
#include "test.level.cpp"
#include "test.levelgen.cpp"
#include "test.mob.cpp"
#include "test.monster.cpp"
#include "test.playerchar.cpp"
#include "test.potion.cpp"
#include "test.random.cpp"
#include "test.ring.cpp"
#include "test.room.cpp"
#include "test.scroll.cpp"
#include "test.stairs.cpp"
#include "test.terrain.cpp"
#include "test.testable.h"
#include "test.trap.cpp"
#include "test.tunnel.cpp"
#include "test.uistate.cpp"
#include "test.wand.cpp"
#include "test.weapon.cpp"

int main() {

	std::vector<Testable*> tests = {new ArmorTest(),
									new AmuletTest(),
									new CoordTest(),
									new FeatureTest(),
									new FoodTest(),
									new GoldPileTest(),
									new ItemTest(),
									new ItemZoneTest(),
									new LevelTest(),
									new LevelGenTest(),
									new MobTest(),
									new MonsterTest(),
									new PlayerCharTest(),
									new PotionTest(),
									new RandomTest(),
									new RingTest(),
									new RoomTest(),
									new ScrollTest(),
									new StairsTest(),
									new TerrainTest(),
									new TrapTest(),
									new TunnelTest(),
									new WandTest(),
									new WeaponTest(),
									new UIStateTest()};

	for (Testable* t : tests){
		t->test();
		delete t;
	}

	return 0;
}
