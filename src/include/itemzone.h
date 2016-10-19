#pragma once

#include <vector>

#include "item.h"

class ItemZone {
	public:
		ItemZone();
		Item* operator[](int);
		void add(Item&);
		bool contains(Item*);
		bool contains(const std::string&);
		std::vector<Item*> getContents();
		bool remove(Item*);

	private:
		struct KeysItem {
			Item* item;
			int quantity;
			KeysItem(Item* item, int quantity)
				: item(item)
				, quantity(quantity)
			{}
		};
		std::map<char, KeysItem> contents;
		static const int MAX_SIZE = 23;
		const std::string KEYS = "abcdefghijklmnopqrstuvwxyz";
		char getFreeChar();
		KeysItem* getItem(char);
		KeysItem* getItem(Item&);
};
