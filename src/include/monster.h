/**
 * @file monster.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Monster class
 */ 

#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "coord.h"
#include "level.h"
#include "mob.h"

/** Tuple representing various Monster types (<Armor, Carry Chance, Attacks, XP, Flags, Monster Level, HP, Name, Dungeon Level Range>) */
using MONSTER_TUPLE_TYPE = std::tuple<int, int, std::vector<std::pair<int, int> >, int, const char*, int, std::pair<int, int>, std::string, std::pair<int, int> >;

class PlayerChar;

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
		 *
		 * @exception  e Illegal argument exception is thrown if an unknown symbol is given
		 */
		Monster(char, Coord);

		/**
		 * @brief      Monster flags denoting behavioural patterns.
		 */
		enum Behaviour {
			AGGRESSIVE,
			CANCELLED,
			CONFUSED,
			CONFUSES,
			DRAINS_LIFE,
			DROPS_LEVEL,
			FLAMES,
			FLYING,
			FREEZES,
			FROZEN,
			GREEDY,
			HASTED,
			HELD,
			INVISIBLE,
			RANGED,
			REGENERATIVE,
			RUSTS,
			SLOWED,
			STATIONARY,
			STINGS };

		/**
		 * @brief      Adds a flag to this Monster.
		 *
		 * @param[in]  flag Flag to add to this Monster.
		 */
		void addFlag(Monster::Behaviour);

		/**
		 * @brief      Freezes the Monster for the given number of turns.
		 *
		 * @param[in]  turns Number of turns to freeze the Monster
		 */
		void addFrozenTurns(int);

		/**
		 * @brief	Aggrevates this monster to attack the player.
		 *
		 */
		void aggrevate();

		/**
		 * @brief      Attempts to attack a nearby Player Character.
		 *
		 * @param      level Reference to the current Level
		 */
		void attack(Level*);

		/**
		 * @brief      Confuse Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackConfuse(PlayerChar*);

		/**
		 * @brief      Drain life Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackDrainLife(PlayerChar*);

		/**
		 * @brief      Drop level Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackDropLevel(PlayerChar*);

		/**
		 * @brief      Freezes Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackFreeze(PlayerChar*);

		/**
		 * @brief      Gold steal Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackGold(PlayerChar*);

		/**
		 * @brief      Rust Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackRust(PlayerChar*);

		/**
		 * @brief      Sting Monster attack
		 *
		 * @param      player Reference to the PlayerChar
		 */
		void attackSting(PlayerChar*);

		/**
		 * @brief      Calculates the damage of this Monster.
		 *
		 * @return     The computed damage.
		 */
		int calculateDamage();

		/**
		 * @brief	Calculates the hit chance of this Monster.
		 *
		 * @param	Reference to the player character
		 *
		 * @return	The computed hit chance.
		 */
		int calculateHitChance(PlayerChar*);

		/**
		 * @brief Returns the effective armor of this Monster.
		 * 
		 * @return The effective armor of this Monster.
		 */
		int getArmorRating();

		/**
		 * @brief      Gets the carry chance of this Monster.
		 *
		 * @return     The carry chance of this Monster.
		 */
		int getCarryChance();

		/**
		 * @brief      Returns this Monster's turn delay.
		 *
		 * @return     The delay.
		 */
		int getDelay();

		
		/**
		 * @brief	Returns the name of this Monster.
		 *
		 * @return	The name of this Monster.
		 */ 
		std::string getName();

		/**
		 * @brief	Returns the name of this Monster (factoring in invisiblity).
		 *
		 * @return	The name of this Monster.
		 */ 
		std::string getName(PlayerChar*);

		/**
		 * @brief      Gets the valid Monster symbols based on the current dungeon depth.
		 *
		 * @param[in]  depth Current dungeon depth
		 *
		 * @return     Vector of valid Monster symbols.
		 */
		static std::vector<char> getSymbolsForLevel(int);

		/**
		 * @brief      Gets the valid Monster symbols for a treasure room based on the current dungeon depth.
		 *
		 * @param[in]  depth Current dungeon depth
		 *
		 * @return     Vector of valid Monster symbols.
		 */
		static std::vector<char> getSymbolsForTreasure(int);

		/*
		 * @brief	Determines whether or not this Monster has the given behaviour flag.
		 *
		 * @return	True if this Monster has the behaviour flag, False otherwise.
		 */
		bool hasFlag(Behaviour);

		/**
		 * @brief	Override mob implementation to aggrevate monster.
		 * 
		 * @see		aggrevate
		 */
		virtual void hit(int dmgAmount);

		/**
		 * @brief	Gets the Monster awake state.
		 *
		 * @return	True if the Monster is awake, False otherwise.
		 */
		bool isAwake();

		/**
		 * @brief	Determines whether or not this monster should be visible to the PlayerChar.
		 *
		 * @return	True if it is visible, False otherwise.
		 */ 
		bool isVisible();

		/**
		 * @brief      Removes a flag from the Monster.
		 *
		 * param[in]	flag Flag to remove from this Monster.   
		 */
		void removeFlag(Monster::Behaviour);
	
		/**
		 * @brief	Sets the Monster awake state.
		 *
		 * @param	New awake state
		 */ 
		void setAwake(bool);

		/**
		 * @brief	Sets this Monster's visibility to the given value.
		 *
		 * @param	visible New value of Monster's visibility.
		 */ 
		void setVisible(bool);

		/**
		 * @brief      Performs the actions that make up a Monster's turn.
		 *
		 * @param      level Reference to the current Level
		 *
		 * @return     Value denoting the consequential turn delay.
		 */
		virtual int turn(Level*);

		/**
		 * @brief	Creates a random monster.
		 *
		 * @return	Totally random monster (can be out of depth).
		 */
		static Monster* randomMonster();

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
		 * Determines whether or not this Monster will perform actions during its turn.
		 */
		bool awake;

		/**
		 * Chance this Monster is carrying an Item.
		 */
		int carryChance;

		/**
		 * Determines whether or not this Monster is currently chasing the player.
		 */
		bool chasing;

		/**
		 * <Dice Rolls, Die Value> pair denoting the damage of this Monster.
		 */
		std::vector<std::pair<int,int> > damage;

		/**
		 * Monster behavioural flags.
		 */
		std::set<Behaviour> flags;

		/**
		 * Number of turns this Monster is frozen.
		 */
		int frozenTurns;

		/** Determines whether or not this Monster should be visible to the PlayerChar */
		bool visible;

		/** Possibilities for a randomly assigned foreground color for the mob. */
		static const std::vector<TCODColor> possibleColors;
};
