#pragma once

#include <map>
#include <string>

#include "coord.h"
#include "feature.h"

class Level;

class Item : public Feature {
	public:
		enum Context {FLOOR, INVENTORY};
		
		Item(char, Coord, Context, std::string, std::string, std::string, unsigned char, bool, bool);

		bool operator==(const Item&) const;
		bool operator<(const Item&) const;

		Context getContext();
		std::string getDisplayName();
		std::string getName();
		unsigned char getType();
		bool isIdentified();
		bool isStackable();
		bool isThrowable();
		void setIdentified(bool);

	private:
		static std::map<std::string, std::map<unsigned char, bool>> identified;

		bool canStack;
		bool canThrow;
		std::string className;
		Context context;
		std::string name;
		std::string pseudoName;
		unsigned char type;
};
