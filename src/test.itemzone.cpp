/**
 * @file test.itemzone.cpp
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Global members
 */ 

#include "include/armor.h"
#include "include/coord.h"
#include "include/item.h"
#include "include/itemzone.h"
#include "include/potion.h"
#include "test.testable.h"

class ItemZoneTest : public Testable {
	public:
		ItemZoneTest() {}

		void test() {
			comment("Testing ItemZone");

			auto zone = ItemZone();
			auto pot = new Potion(Coord(0,0), Item::Context::INVENTORY, 1);
			auto pot2 = new Potion(Coord(0,0), Item::Context::INVENTORY, 2);
			zone.add(*pot);
			zone.add(*pot2);
			assert(zone.contains(pot), "Zone should contain item");
			assert(zone.contains(pot2), "Zone should contain other item");
			assert(zone.getSize() > 0, "Zone should not be empty");
			auto contents = zone.getContents();
			assert(contents.size() == 2, "Contents of zone should be size 2");
			assert(contents['a'].front() == pot, "First item should be bound to 'a' key");
			assert(contents['b'].front() == pot2, "Second item should be bound to 'b', key");
			assert(contents['a'].size() == 1, "Should only be 1 of first item");
			assert(contents['b'].size() == 1, "Should only be 1 of second item");

			zone.remove(pot);
			delete pot;

			contents = zone.getContents();
			assert(contents.size() == 1, "First item should no longer be in the zone");
			assert(contents['b'].front() == pot2, "Second item hotkey should not have changed");

			zone.remove(pot2);
			delete pot2;

			std::vector<Armor*> armors;
			for (int i = 0; i < 500; ++i) {
				armors.push_back(new Armor(Coord(0,0)));
				zone.add(*armors.back());
			}
			assert(zone.getCurrWeight() <= zone.getMaxWeight(), "Zone should respect weight limits");
			for (auto a : armors) {
				delete a;
			}
			armors.clear();

			comment("Finished ItemZone tests");
		}

};
