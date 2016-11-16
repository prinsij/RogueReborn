/**
 * @file playerchar.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the PlayerChar class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "goldpile.h"
#include "itemzone.h"
#include "mob.h"

class Level;
class Food;
class Item;
class Ring;
class Weapon;
class Armor;
class Wand;
class Scroll;
class Potion;
class Monster;

/**
 * @brief      Models the user-controlled player character.
 */
class PlayerChar : public Mob {
	public:
		/**
		 * @brief      Constructs a PlayerChar instance.
		 *
		 * @param[in]  location  PlayerChar location
		 * @param[in]  name  PlayerChar name
		 */
		PlayerChar(Coord, std::string);

		enum Condition {BLIND,
			CONFUSED,
			CONFUSE_MONSTER,
			DETECT_MONSTER,
			DETECT_OBJECTS,
			DIGESTION,
			FAINTING,
			HALLUCINATING,
			HASTED,
			IMMOBILIZED,
			LEVITATING,
			MAINTAIN_ARMOR,
			RANDOM_TELEPORTATION,
			REGENERATION,
			SEARCH,
			SEE_INVISIBLE,
			SLEEPING,
			SLOWED,
			STEALTHY,
			SUSTAIN_STRENGTH};

		/**
		 * @brief      Activates the provided item
		 *
		 * @param      item  Item to be activated
		 */
		void activateItem(Item*);


		/**
		 * @brief	Adds the given experience to the PlayerChar
		 *
		 * @param	exp Experience to be added
		 */
		void addExp(int);

		/**
		 * @brief      Appends the given entry to the log.
		 *
		 * @param[in]  entry  Entry to be appended to the log.
		 */
		void appendLog(std::string);

		/**
		 * @brief Applies the given condition to the PlayerChar for the provided number of turns.
		 *
		 * @param condition State to be applied to the player
		 * @param turns Number of turns the condition should last (-1 for continuous)
		 */
		void applyCondition(Condition, int);

		/**
		 * @brief      Attacks the given Mob.
		 *
		 * @param      monster  Monster to be attacked.
		 */
		void attack(Monster*);

		/**
		 * @brief	Calculates the damage the PlayerChar will inflict.
		 *
		 * @return	The damage to be inflicted.
		 */
		int calculateDamage();

		/**
		 * @brief	Calculates the hit chance of the PlayerChar.
		 *
		 * @param	monster Moster to be hit
		 *
		 * @return	The chance the PlayerChar will hit their target.
		 */
		int calculateHitChance(Monster*);

		/**
		 * @brief	Increases the current HP of the PlayerChar by the passed parameter.
		 *
		 * @param	amount Amount to change the current HP.
		 */
		void changeCurrentHP(int);

		/**
		 * @brief	Increases the current strength of the PlayerChar by the passed parameter.
		 *
		 * @param	amount Amount to change the current strength.
		 */
		void changeCurrentStrength(int);

		/**
		 * @brief	Increases the maximum stength of the PlayerChar by the passed parameter.
		 *
		 * @param	amount Amount to change the maximum strength.
		 */
		void changeMaxStrength(int);

		/**
		 * @brief	Increases the food life of the PlayerChar by the passed parameter.
		 *
		 * @param	amount Amount to change the food life.
		 */
		void changeFoodLife(int);

		/**
		 * @brief      Adds the gold contained in the given GoldPile to the PlayerChar's gold total.
		 *
		 * @param      goldPile GoldPile to be harvested.
		 */
		void collectGold(GoldPile*);

		/**
		 * @brief      Attemps to drop the given Item.
		 *
		 * @param      item  Item to be dropped
		 * @param      level Reference to the current Level
		 *
		 * @return     True if the Item was successfully dropped, False otherwise.
		 */
		bool dropItem(Item*, Level*);

		/**
		 * @brief      Decrements the level of the PlayerChar.
		 */
		void dropLevel();

		/**
		 * @brief      Attempts to eat the given Food.
		 *
		 * @param      food Food to be eaten.
		 */
		void eat(Food*);

		/**
		 * @brief      Attempts to equip the given Armor.
		 *
		 * @param      armor Armor to be equipped.
		 */
		void equipArmor(Armor*);

		/**
		 * @brief      Attempts to equip the given Ring on the PlayerChar's left hand.
		 *
		 * @param      ring Ring to be equipped.
		 */
		void equipRingLeft(Ring*);

		/**
		 * @brief      Attempts to equip the given Ring on the PlayerChar's right hand.
		 *
		 * @param      ring Ring to be equipped.
		 */
		void equipRingRight(Ring*);

		/**
		 * @brief      Attempts to equip the given Weapon.
		 *
		 * @param      weapon Weapon to be equipped.
		 */
		void equipWeapon(Weapon*);

		/**
		 * @brief      Gets the equipped armor.
		 *
		 * @return     The armor the PlayerChar is wearing.
		 */
		Armor* getArmor();

		/**
		 * @brief	Gets the PlayerChar's dexterity.
		 *
		 * @return	The PlayerChar's dexterity.
		 */
		int getDexterity();

		/**
		 * @brief      Gets the PlayerChar's turn delay.
		 *
		 * @return     The turn delay.
		 */
		int getDelay();

		/*
		 * @brief	Gets the PlayerChar's chance to reveal secrets.
		 * @see		SEARCH_CHANCE
		 *
		 * @return	The chance out of 1 to reveal a secret when searching.
		 */
		float getSearchChance();

		/**
		 * @brief	Gets the PlayerChar's search radius.
		 * see		SEARCH_RADIUS
		 *
		 * @return	Distance (taxicab) in which the player will
		 *			spot secrets when searching.
		 */
		int getSearchRadius();

		/**
		 * @brief	Gets the PlayerChar's food life.
		 *
		 * @return	The PlayerChar's food life.
		 */
		int getFoodLife();

		/**
		 * @brief	Gets the PlayerChar's food status
		 *
		 * @return	This PlayerChar's food status (NULL is full)
		 */
		std::string getFoodStatus();

		/**
		 * @brief      Gets the PlayerChar's gold total.
		 *
		 * @return     The PlayerChar's gold total.
		 */
		int getGold();

		/**
		 * @brief      Gets the PlayerChar's inventory.
		 *
		 * @return     The PlayerChar's inventory.
		 */
		ItemZone& getInventory();

		/**
		 * @brief		Gets the level of this PlayerChar.
		 *
		 * @return		The level of this PlayerChar.
		 */
		int getLevel();

		/**
		 * @brief      Gets the references to the equipped Rings.
		 *
		 * @return     The references to the Rings.
		 */
		std::pair<Ring*, Ring*> getRings();

		/**
		 * @brief      Gets the PlayerChar's strength.
		 *
		 * @return     The PlayerChar's strength.
		 */
		int getStrength();

		/**
		 * @brief      Gets the PlayerChar's maximum strength.
		 *
		 * @return     The PlayerChar's maximum strength.
		 */
		int getMaxStrength();

		/**
		 * @brief      Gets the PlayerChar's sight radius.
		 *
		 * @return     The PlayerChar's sight radius.
		 */
		int getSightRadius();

		/**
		 * @brief		Getter for currently equipped weapon.
		 *
		 * @param		weapon Weapon player is wielding (maybe none)
		 */
		Weapon* getWeapon();

		/**
		 * @brief      Determines whether or not PlayerChar has the Amulet of Yendor.
		 *
		 * @return     True if PlayerChar has the Amulet, False otherwise.
		 */
		bool hasAmulet();

		/**
		 * @brief Determines whether or not this PlayerChar is affected by the given condition.
		 *
		 * @param  condition Condition to check
		 * @return True if PlayerChar is currently affected by condition, False otherwise.
		 */
		bool hasCondition(Condition);

		/**
		 * @brief      Inflicts HP loss to this PlayerChar based on the given damage.
		 *
		 * @param[in]  damage Baseline damage to be inflicted
		 */
		void hit(int);

		/**
		 * @brief	Relocates the PlayerChar and updates the food life.
		 *
		 * @param	location New PlayerChar location
		 * @param	level Reference to the current level
		 */
		bool move(Coord, Level*);

		/**
		 * @brief      Attempts to place the provided Item in the PlayerChar's inventory.
		 *
		 * @param      item Item to be inserted into the PlayerChar's inventory.
		 */
		void pickupItem(Item*);

		/**
		 * @brief      Attempts to apply the effects of the provided Potion to the given Mob.
		 *
		 * @param      potion  Potion to be quaffed
		 * @param      mob Mob to quaff the Potion
		 */
		void quaff(Potion*, Mob*);

		/**
		 * @brief Increments the PlayerChar's level.
		 */
		void raiseLevel();

		/**
		 * @brief      Attempts to remove the PlayerChar's equipped Armor.
		 *
		 * @return     True if the operation was successful, False otherwise.
		 */
		bool removeArmor();

		/**
		 * @brief	Removes the given condition from the PlayerChar.
		 *
		 * @param	condition Condition to remove
		 */
		void removeCondition(Condition);

		/**
		 * @brief      Attempts to remove the PlayerChar's equipped left Ring.
		 *
		 * @return     True if the operation was successful, False otherwise.
		 */
		bool removeRingLeft();

		/**
		 * @brief      Attempts to remove the PlayerChar's equipped right Ring.
		 *
		 * @return     True if the operation was successful, False otherwise.
		 */
		bool removeRingRight();

		/**
		 * @brief      Attempts to remove the PlayerChar's equipped Weapon.
		 *
		 * @return     True if the operation was successful, False otherwise.
		 */
		bool removeWeapon();

		/**
		 * @brief	Sets the PlayerChar's dexterity
		 *
		 * @param	dexterity The PlayerChar's new dexterity
		 */
		void setDexterity(int);

		/**
		 * @brief	Sets the food life of the PlayerChar
		 *
		 * @param	foodLife The new food life of the PlayerChar
		 */
		void setFoodLife(int);

		/**
		 * @brief      Sets the gold.
		 *
		 * @param[in]  gold	New amount of gold
		 */
		void setGold(int);

		/**
		 * @brief	Sets the strength of the PlayerChar.
		 *
		 * @param	strength The new strength of the PlayerChar
		 */
		void setStrength(int);

		/**
		 * @brief	Updates this Player's states
		 *
		 * @return	The turn delay.
		 */
		int update();

		/**
		 * @brief	Updates the PlayerChar's health according to i*/
		void updateHealthRegen();

		/**
		 * @brief      Gets the PlayerChar's log.
		 *
		 * @return     The PlayerChar's log.
		 */
		std::vector<std::string>& getLog();

	private:
		/** Possible food states of the PlayerChar */
		enum FoodStates {FULL, HUNGRY, WEAK, FAINT, STARVE};

		/** Current conditions acting upon the player (<Condition, Steps Left>) */
		static std::map<Condition, int> conditions;

		/** Experience bounds corresponding to each level */
		static std::vector<int> levelExpBounds;

		/** Food life bounds corresponding to hunger, fainting, etc. */
		static std::vector<int> foodLifeBounds;

		/** PlayerChar's current strength */
		int currentStr;

		/** PlayerChar's dexterity (increases hit chance) */
		int dexterity = 0;

		/** PlayerChar's current food value */
		int foodLife;

		/** PlayerChar's food status */
		FoodStates foodStatus;

		/** PlayerChar's current gold quantity */
		int gold;

		/** PlayerChar's inventory to store unequipped Items */
		ItemZone inventory;

		/** Reference to the PlayerChar's equipped Armor */
		Armor* itemArmor;

		/** Reference to the PlayerChar's equipped left Ring */
		Ring* itemRingLeft;

		/** Reference to the PlayerChar's equipped right Ring */
		Ring* itemRingRight;

		/** Reference to the PlayerChar's equipped Weapon */
		Weapon* itemWeapon;

		/** Vector of log messages */
		std::vector<std::string> log;

		/** Maximum size of the PlayerChar's log */
		static const int MAX_LOG = 30;

		/** PlayerChar's maximum strength */
		int maxStr;

		/** PlayerChar's move counter */
		int moves;

		/** Maximum moves value */
		static const int MOVES_RESET = 99999;

		/** PlayerChar's starting armor rating */
		static const int START_ARMOR = 1;

		/** PlayerChar's starting experience value */
		static const int START_EXP = 0;

		/** PlayerChar's starting gold value */
		static const int START_GOLD = 0;

		/** PlayerChar's starting HP value */
		static const int START_HP = 12;

		/** PlayerChar's starting level */
		static const int START_LEVEL = 1;

		/** PlayerChar's starting strength value */
		static const int START_STR = 16;

		/** PlayerChar's starting sight radius */
		static const int SIGHT_RADIUS = 1;

		/** PlayerChar's starting food value */
		static const int START_FOOD = 1250;

		/** Chance in to discover a nearby secret
		 *  with a search (out of 1).
		 */
		static constexpr float SEARCH_CHANCE = .4;

		/** Distance (taxicab) the player searches
		 *  when looking for secrets.
		 */
		static constexpr int SEARCH_RADIUS = 2;
};
