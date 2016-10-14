#pragma once

#include <string>

#include "coord.h"
#include "feature.h"

class Item : public Feature {
	public:
		enum Context {FLOOR, INVENTORY};
		
		Item(char, Coord, Context, std::string, std::string, unsigned char, bool, bool);

		bool operator==(const Item&) const;
		bool operator<(const Item&) const;

		Context getContext();
		std::string getDisplayName();
		bool getIdentified();
		std::string getName();
		unsigned char getType();
		bool isStackable();
		bool isThrowable();
		void setIdentified(bool);

	private:
		bool canStack;
		bool canThrow;
		Context context;
		bool identified;
		std::string name;
		std::string pseudoName;
		unsigned char type;
};
