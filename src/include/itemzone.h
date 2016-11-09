/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: itemzone.h
 */ 

#pragma once

#include <vector>

#include "item.h"

/** Container for items.
 * @see Item
 * Tracks stackability and how it relates
 * to capacity, provides utility functions,
 * and tracks persistent hotkeys.
 */
class ItemZone {
	public:
		/** Internal representation of items,
		 *  helps for stackability tracking.
		 */
		struct KeysItem {
			/** Item this corresponds to. */
			Item* item;
			/** Number in this stack (should be only
			 *  1 stack per ItemZone).
			 */
			int quantity;
			/** Constructor. */
			KeysItem(Item* item, int quantity)
				: item(item)
				, quantity(quantity)
			{}
		};
		/** Constructor for empty container. */
		ItemZone();
		/** Access item at index, as if ItemZone
		 *  was just an array.
		 */
		Item* operator[](int);
		/** Add item to ItemZone, stacking if necessary. */
		void add(Item&);
		/** Check if ItemZone contains >= 1 copies of item. */
		bool contains(Item*);
		/** Check if item with given name is in ItemZone. */
		bool contains(const std::string& name);
		/** Return the contents of the zone directly. */
		std::map<char, KeysItem>& getContents();
		/** Remove the given item from the zone, potentially
		 *  destacking if necessary
		 */
		bool remove(Item*);

	private:
		/** Data structure which stores items. */
		std::map<char, KeysItem> contents;
		/** Maximum capacity of zone, not counting stacks. */
		static const int MAX_SIZE = 23;
		/** List of all allowed hotkeys for items. */
		const std::string KEYS = "abcdefghijklmnopqrstuvwxyz";
		/** Find an allowed hotkey which is not in use.
		 * @see KEYS
		 */
		char getFreeChar();
		/** Return struct corresponding to given hotkey. */
		KeysItem* getItem(char);
		/** Return struct corresponding to given item. */
		KeysItem* getItem(Item&);
};
