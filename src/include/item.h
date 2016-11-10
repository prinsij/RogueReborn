/**
 * @file item.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Item class
 */ 

#pragma once

#include <map>
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
		static std::vector<std::string> shuffleNameVector(std::vector<std::string>);

		enum Context {FLOOR, INVENTORY};

		Item(char, Coord, Context, std::string, std::string, int, bool, bool);
		Item(char, Coord, Context, std::string, std::string, std::string, int, bool, bool);

		bool operator==(const Item&) const;
		bool operator<(const Item&) const;

		Context getContext();
		void setContext(Context);
		std::string getDisplayName();
		std::string getName();
		int getType();
		bool isIdentified();
		bool isStackable();
		bool isThrowable();
		void setIdentified(bool);

	protected:
		static std::map<std::string, std::map<int, bool> > identified;

		bool canStack;
		bool canThrow;
		std::string className;
		Context context;
		bool cursed;
		std::string name;
		std::string pseudoName;
		int type;
};