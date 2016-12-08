/**
 * @file test.feature.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the FeatureTest class
 */ 

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "include/feature.h"
#include "test.testable.h"

class FeatureTest : public Testable {
	public:
		FeatureTest(){}

		void test(){
			comment("Commencing Feature tests...");

			try {
				Feature feature = Feature('~', Coord(0,0), false, TCODColor::white);
				assert(true, "Created Feature");
			} catch (const std::exception& e) {
				assert(false, "Failure creating Feature");
			}

			Feature feature = Feature('~', Coord(0,0), false, TCODColor::white);
			assert(feature.getSymbol() == '~', "Feature Symbol Check");
			assert(!feature.getVisible(), "Feature Visible Check");
			feature.setVisible(true);
			assert(feature.getVisible(), "Feature Visible Check");
			assert(feature.getLocation() == Coord(0,0), "Feature Location Check");

			comment("Finished Feature tests.");
		}
};
