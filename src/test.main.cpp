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

	ArmorTest().test();
	AmuletTest().test();
	CoordTest().test();
	FeatureTest().test();
	FoodTest().test();
	GoldPileTest().test();
	ItemTest().test();
	ItemZoneTest().test();
	// LevelTest().test();
	// LevelGenTest().test();
	MobTest().test();
	MonsterTest().test();
	PlayerCharTest().test();
	PotionTest().test();
	RandomTest().test();
	RingTest().test();
	RoomTest().test();
	ScrollTest().test();
	StairsTest().test();
	TerrainTest().test();
	// TrapTest().test();
	// TunnelTest().test();
	// WandTest().test();
	// WeaponTest().test();
	// UIStateTest().test();

	return 0;
}
