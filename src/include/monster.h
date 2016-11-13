/**
 * @file monster.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Monster class
 */ 

#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "coord.h"
#include "level.h"
#include "mob.h"

/** Tuple representing various Monster types (<Armor, Carry Chance, Attacks, XP, Flags, Monster Level, HP, Name, Dungeon Level Range>) */
using MONSTER_TUPLE_TYPE = std::tuple<int, int, std::vector<std::pair<int, int> >, int, const char*, int, std::pair<int, int>, std::string, std::pair<int, int> >;

//class Level;

/**
 * Models a monster in the dungeon.
 */
class Monster : public Mob {
	public:
		/**
		 * @brief      Constructs a Monster instance of the given symbol type.
		 *
		 * @param[in]  symbol  Monster symbol
		 * @param[in]  location  Monster location
		 */
		Monster(char, Coord);

		/**
		 * @brief      Attempts to attack a nearby Player Character.
		 *
		 * @param      level Reference to the current Level
		 */
		void attack(Level*);

		/**
		 * @brief      Calculates the damage of this Monster.
		 *
		 * @return     The computed damage.
		 */
		int calculateDamage();

		/**
		 * @brief      Gets the carry chance of this Monster.
		 *
		 * @return     The carry chance of this Monster.
		 */
		int getCarryChance();

		/**
		 * @brief      Gets the valid Monster symbols based on the current dungeon depth.
		 *
		 * @param[in]  depth Current dungeon depth
		 *
		 * @return     Vector of valid Monster symbols.
		 */
		std::vector<char> getSymbolsForLevel(int);

		/**
		 * @brief      Gets the valid Monster symbols for a treasure room based on the current dungeon depth.
		 *
		 * @param[in]  depth Current dungeon depth
		 *
		 * @return     Vector of valid Monster symbols.
		 */
		std::vector<char> getSymbolsForTreasure(int);

		/**
		 * @brief      Performs the actions that make up a Monster's turn.
		 *
		 * @param      level Reference to the current Level
		 *
		 * @return     Value denoting the consequential turn delay.
		 */
		virtual int turn(Level*);

	private:
		/**
		 * Map of the following form: { Monster Symbol: Monster Tuple }
		 */
		static std::map<char, MONSTER_TUPLE_TYPE > templateMap;

		/**
		 * @brief      Relocates the Monster during the present turn.
		 *
		 * @param      level Reference to the current Level
		 */
		void relocate(Level*);

		/**
		 * Determines whether or not this monster will perform actions during its turn.
		 */
		bool awake;

		/**
		 * @brief      Monster flags denoting behavioural patterns.
		 */
		enum Behaviour {AGGRESSIVE, FLYING, REGENERATIVE, GREEDY, INVISIBLE};

		/**
		 * Chance this Monster is carrying an Item.
		 */
		int carryChance;

		/**
		 * <Dice Rolls, Die Value> pair denoting the damage of this Monster.
		 */
		std::vector<std::pair<int,int> > damage;

		/**
		 * Monster behavioural flags.
		 */
		std::vector<Behaviour> flags;
};