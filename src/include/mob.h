/**
 * @file mob.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Mob class
 */ 

#pragma once

#include <string>

#include "coord.h"

class Level;

/**
 * Models a creature in the dungeon, could
 * be the player or a monster.
 */
class Mob {
	public:
		/** Constructor used by monsters. */
		Mob(char, Coord);
		/** Constructor
		 * @see armor
		 * @see exp
		 * @see maxHP
		 * @see level
		*/
		Mob(char, Coord, std::string, int armor, int exp, int mobHP, int level);

		static int diceSum(int, int);

		//virtual void attack(Mob*) = 0;
		virtual int calculateDamage() = 0;
		/** Setter for armor.
		 * @see armor
		 */
		void changeArmor(int);
		/** Getter for armor.
		 * @see armor
		 */
		virtual int getArmor();
		/** Getter for XP.
		 * @see exp
		 */
		int getExperience();
		/** Getter for HP.
		 * @see currentHP
		 */
		int getHP();
		/** Getter for max HP.
		 * @see maxHP
		 */
		int getMaxHP();
		/** Getter for mob level.
		 * @see level
		 */
		int getLevel();
		/** Getter for mob location.
		 * Can be edited because it returns
		 * a reference
		 * @see location
		 */
		Coord& getLocation();
		/** Getter for name.
		 * @see name
		 */
		std::string getName();
		/** Getter for symbol.
		 * @see symbol
		 */
		char getSymbol();
		/** Called by other entities when they
		 *  deal damage.
		 * @see currentHP
		 */
		virtual void hit(int);
		/**
		 * @brief	Determines if this mob is dead
		 *
		 * @return	True if this mob is dead, false otherwise
		 */
		bool isDead();
		/** Add current location and param together.
		 * @see location
		 */
		void moveLocation(Coord);
		/** Setter for current HP.
		 * @see currentHP
		 */
		bool setCurrentHP(int);
		/** Setter for location.
		 * @see location
		 */
		void setLocation(Coord);
		/** Setter for max hitpoints
		 * @see maxHP
		 */
		void setMaxHP(int);
		/** Mob enacts its turn on the level,
		 *  returns number of ticks it took.
		 */
		virtual int turn(Level*);

		/** Destructor. */
		virtual ~Mob();

	protected:
		/** More armor makes it more difficult for enemies to
		    hit the mob. */
		int armor;
		/** More hitpoints indicates the mob is healthier */
		int currentHP;
		/** Indicates whether or not this mob is dead */
		bool dead;
		/** More exp indicates the mob is closer to leveling up. */
		int exp;
		/** Higher level characters are more powerful. */
		int level;
		/** Current location within the level. */
		Coord location;
		/** Maximum number of hitpoints. */
		int maxHP;
		/** Name of the mob. */
		std::string name;

	private:
		/** Ascii symbol which represents the mob */
		char symbol;
};
