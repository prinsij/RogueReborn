/**
 * @file test.main.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Global members
 */ 

#include <vector>

#include "test.testable.h"
#include "test.armor.cpp"
#include "test.amulet.cpp"
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
#include "test.trap.cpp"
#include "test.tunnel.cpp"
#include "test.uistate.cpp"
#include "test.wand.cpp"
#include "test.weapon.cpp"

int main() {

	std::vector<Testable*>* tests = new std::vector<Testable*>();
	tests->push_back(new ArmorTest());
	tests->push_back(new AmuletTest());
	tests->push_back(new CoordTest());
	tests->push_back(new FeatureTest());
	tests->push_back(new FoodTest());
	tests->push_back(new GoldPileTest());
	tests->push_back(new ItemTest());
	tests->push_back(new ItemZoneTest());
	tests->push_back(new LevelTest());
	tests->push_back(new LevelGenTest());
	tests->push_back(new MobTest());
	tests->push_back(new MonsterTest());
	// tests->push_back(new PlayerCharTest());
	// tests->push_back(new PotionTest());
	// tests->push_back(new RandomTest());
	// tests->push_back(new RingTest());
	// tests->push_back(new RoomTest());
	// tests->push_back(new ScrollTest());
	// tests->push_back(new StairsTest());
	// tests->push_back(new TerrainTest());
	// tests->push_back(new TrapTest());
	// tests->push_back(new TunnelTest());
	// tests->push_back(new WandTest());
	// tests->push_back(new WeaponTest());
	// tests->push_back(new UIStateTest());

	std::vector<Testable*>::iterator it;

	for (it = tests->begin(); it < tests->end(); it++){
		(*it)->test();
		delete (*it);
	}

	delete tests;

	return 0;
}
