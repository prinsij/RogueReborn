#include "item.h"
#include <vector>

#ifndef ITEMZONE_H
#define ITEMZONE_H

class ItemZone {
	public:
		ItemZone();
		Item operator[](int);
		bool remove(Item&);
		void add(Item&);
		bool contains(Item&);
	private:
		std::vector<Item> contents;
};

#endif
