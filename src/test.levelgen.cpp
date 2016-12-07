/**
 * @file test.levelgen.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Member definitions for the LevelGenTest class
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "include/level.h"
#include "include/stairs.h"
#include "test.testable.h"

class LevelGenTest : public Testable {
	public:
		LevelGenTest(){}

		const int NUMBER_OF_TIMES_TO_BFS = 1000;
		const int NUMBER_OF_LEVELS_TO_TEST = 10;

		void test(){

			comment("Commencing LevelGen tests");

			PlayerChar* player = new PlayerChar(Coord(0,0), "Test");
			Level* level;

			for (auto i = 0; i < NUMBER_OF_LEVELS_TO_TEST; i++){
				level = new Level(1, player);
				level->generate();


				bool probablyOk = true;
				for (auto j = 0; j < NUMBER_OF_TIMES_TO_BFS; j++){
					probablyOk *= level->bfsPerp(level->getRandomEmptyPosition(), level->getRandomEmptyPosition()).size() > 0;
				}
				assert(probablyOk, "Level passes random path tests");



				std::vector<Room> rooms = level->getRooms();
				bool roomsConnected = true;
				for (Room source : rooms){
					for (Room target : rooms){
						if (&source != &target){
							roomsConnected *= level->bfsPerp(
							Generator::randPosition(source.getPosition1(), source.getPosition2()),
							Generator::randPosition(target.getPosition1(), target.getPosition2())).size() > 0;
						}
					}
				}
				assert(roomsConnected, "Level is connected");





				std::vector<Feature*> features = level->getFeatures();

				bool hasStairs = false;
				for (Feature* f : features){
  					Stairs* stair = dynamic_cast<Stairs*>(f);
  					if (stair != NULL){
  						hasStairs = true;
  					}
				}
				assert(hasStairs, "Level has stairs");

				bool hasAtLeastOneGold = false;
				for (Feature* f : features){
  					GoldPile* gp = dynamic_cast<GoldPile*>(f);
  					if (gp != NULL){
  						hasAtLeastOneGold = true;
  					}
				}
				assert(hasAtLeastOneGold, "Level has at least one gold pile");

				//All other features (wands, etc.) are placed the same way as gold

				delete level;
			}

			delete player;

			comment("Finished LevelGen tests");
		}
};
