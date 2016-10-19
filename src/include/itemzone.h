#pragma once

#include <vector>

#include "item.h"

class ItemZone {
	public:
		ItemZone();
		Item operator[](int);
		void add(Item&);
		bool contains(Item*);
		bool contains(const std::string&);
		std::vector<Item*> getContents();
		bool remove(Item*);

	private:
		std::vector<Item> contents;
};
