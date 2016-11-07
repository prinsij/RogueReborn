/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: itemzone.h
 */ 

#pragma once

#include <vector>

#include "item.h"

class ItemZone {
	public:
		struct KeysItem {
			Item* item;
			int quantity;
			KeysItem(Item* item, int quantity)
				: item(item)
				, quantity(quantity)
			{}
		};
		ItemZone();
		Item* operator[](int);
		void add(Item&);
		bool contains(Item*);
		bool contains(const std::string&);
		std::map<char, KeysItem>& getContents();
		bool remove(Item*);

	private:

		std::map<char, KeysItem> contents;
		static const int MAX_SIZE = 23;
		const std::string KEYS = "abcdefghijklmnopqrstuvwxyz";
		char getFreeChar();
		KeysItem* getItem(char);
		KeysItem* getItem(Item&);
};