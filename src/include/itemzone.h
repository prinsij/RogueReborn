#include "item.h"
#include <vector>

#ifndef ITEMZONE_H
#define ITEMZONE_H

class ItemZone {
	public:
		Item operator[](int);
		bool remove(Item);
		void add(Item);
	private:
		std::vector<Item> contents;
};

#endif
