/**
 * @file item.h
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Member declarations for the Item class
 */ 

#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

#include "coord.h"
#include "feature.h"

class Level;

/**
 * Represents a generic item.
 */
class Item : public Feature {
	public:
		/**
		 * @brief      Returns a shuffled copy of the provided vector of names.
		 *
		 * @param[in]  nameVector  Vector of names
		 *
		 * @return     The shuffled copy of the provided vector of names.
		 */
		static std::vector<std::string> shuffleNameVector(std::vector<std::string>);

		/**
		 * @brief      Placement context of this Item.
		 */
		enum Context {FLOOR, INVENTORY};

		enum Effect {CURSED, PROTECTED};

		/**
		 * @brief      Constructs an Item instance.
		 *
		 * @param[in]  symbol  Character denoting this Item
		 * @param[in]  location  Item location
		 * @param[in]  context  Item context
		 * @param[in]  className  Name of Item subclass using this constructor
		 * @param[in]  name  Item name
		 * @param[in]  type  Item type
		 * @param[in]  canStack  Denotes whether or not this Item can be stacked in the inventory
		 * @param[in]  canThrow  Denotes whether or not this Item can be thrown
		 * @param[in]  weight  How much the item weighs
		 */
		Item(char, Coord, Context, std::string, std::string, int, bool, bool, int);

		/**
		 * @brief      Constructs an Item instance.
		 *
		 * @param[in]  symbol  Character denoting this Item
		 * @param[in]  location  Item location
		 * @param[in]  context  Item context
		 * @param[in]  className  Name of Item subclass using this constructor
		 * @param[in]  name  Item name
		 * @param[in]  pseudoName  Unidentified Item name
		 * @param[in]  type  Item type
		 * @param[in]  canStack  Denotes whether or not this Item can be stacked in the inventory
		 * @param[in]  canThrow  Denotes whether or not this Item can be thrown
		 * @param[in]  weight  How much the item weighs
		 */
		Item(char, Coord, Context, std::string, std::string, std::string, int, bool, bool, int);

		/**
		 * @brief      Item equality definition
		 *
		 * @param[in]  item  Other equality operand
		 *
		 * @return     True if this Item is equivalent to the given Item, False otherwise
		 */
		bool operator==(const Item&) const;

		/**
		 * @brief      Item 'less than' comparison definition
		 *
		 * @param[in]  item  Other comparison operand
		 *
		 * @return     True if this Item is less than the given Item, False otherwise
		 */
		bool operator<(const Item&) const;

		/**
		 * @brief      Applies the given effect to the Item.
		 *
		 * @param[in]  effect Effect to be applied
		 */
		virtual void applyEffect(Effect);

		/**
		 * @brief      Gets the context.
		 *
		 * @return     The context.
		 */
		Context getContext();

		/**
		 * @brief		Gets the item's weight
		 *
		 * @return		The weight
		 */
		 int getWeight();

		/**
		 * @brief	Gets the subclass name.
		 *
		 * @return	The subclass name.
		 */
		std::string getClassName();

		/**
		 * @brief      Determines if it the Item has the provided effect.
		 *
		 * @param[in]  effect Effect to be checked
		 *
		 * @return     True if the Item has the given effect, False otherwise.
		 */
		bool hasEffect(Effect);

		/**
		 * @brief      Determines if this Item is cursed.
		 *
		 * @return     True if cursed, False otherwise.
		 */
		bool isCursed();

		/**
		 * @brief      Removes the given effect from the Item.
		 *
		 * param[in]   effect Effect to be removed
		 */
		virtual void removeEffect(Effect);

		/**
		 * @brief      Sets the context.
		 *
		 * @param[in]  context  New Item context
		 */
		void setContext(Context);

		/**
		 * @brief      Gets the display name.
		 *
		 * @return     The display name.
		 */
		std::string getDisplayName();

		/**
		 * @brief      Gets the name.
		 *
		 * @return     The name.
		 */
		std::string getName();

		/**
		 * @brief      Gets the type.
		 *
		 * @return     The type.
		 */
		int getType();

		/**
		 * @brief      Determines if the Item is identified.
		 *
		 * @return     True if identified, False otherwise.
		 */
		bool isIdentified();

		/**
		 * @brief      Determines if the Item is stackable.
		 *
		 * @return     True if stackable, False otherwise.
		 */
		bool isStackable();

		/**
		 * @brief      Determines if Item is throwable.
		 *
		 * @return     True if throwable, False otherwise.
		 */
		bool isThrowable();

		/**
		 * @brief      Sets the identified status of this Item type.
		 *
		 * @param[in]  newValue  New identified status of this Item type.
		 */
		void setIdentified(bool);


		static const int BASE_THROW_DMG = 3;

	protected:
		/**
		 * Identification map of the following form: {Class Name : {Type : Status}}
		 */
		static std::map<std::string, std::map<int, bool> > identified;

		/**
		 * Effects applied to the Item.
		 */
		std::set<Effect> effects;

		/**
		 * Denotes whether or not this Item can stack in the inventory.
		 */
		bool canStack;

		/**
		 * Denotes whether or not this Item can be thrown.
		 */
		bool canThrow;

		/**
		 * Name of this Item's subclass.
		 */
		std::string className;

		/**
		 * Context of this Item.
		 */
		Context context;

		/**
		 * Name of this Item.
		 */
		std::string name;

		/**
		 * Name of the unidentified version of this Item.
		 */
		std::string pseudoName;

		/**
		 * Type of this Item.
		 */
		int type;

		/**
		 * How much the item weighs (unit unspecified)
		 */
		 int weight;
};
