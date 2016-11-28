/**
 * @file itemzone.h
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Member declarations for the ItemZone class
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
		/** Constructor for empty container. */
		ItemZone();
		/** Access item at index, as if ItemZone
		 *  was just an array.
		 */
		Item* operator[](int);
		/** Add item to ItemZone, stacking if necessary. */
		bool add(Item&);
		/** Check if ItemZone contains >= 1 copies of item. */
		bool contains(Item*);
		/** Check if item with given name is in ItemZone. */
		bool contains(const std::string& name);
		/** Return the contents of the zone directly. */
		std::map<char, std::vector<Item*> >& getContents();
		/** Remove the given item from the zone, potentially
		 *  destacking if necessary
		 */
		bool remove(Item*);
		/** Return struct corresponding to given hotkey. */
		std::vector<Item*>* getItem(char);
		/** Return the number of distinct items. */
		int getSize();
		/** Return the sum the weight of all inventory contents. */
		int getCurrWeight();
		/** Return the maximum inventory capacity. */
		int getMaxWeight() { return MAX_WEIGHT; }
	private:
		/** Data structure which stores items. */
		std::map<char, std::vector<Item*> > contents;
		/** Maximum capacity of zone, not counting stacks. */
		static const int MAX_SIZE = 23;
		/** List of all allowed hotkeys for items. */
		const std::string KEYS = "abcdefghijklmnopqrstuvwxyz";
		/** Find an allowed hotkey which is not in use.
		 * @see KEYS
		 */
		char getFreeChar();
		/** Return struct corresponding to given item. */
		std::vector<Item*>* getItem(Item&);
		/** Max weight of all inventory contents. */
		static constexpr int MAX_WEIGHT = 55;
};
