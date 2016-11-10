/**
 * @file itemzone.cpp
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member definitions for the ItemZone class
 */ 

#include <algorithm>
#include <map>
#include <vector>

#include "include/itemzone.h"

ItemZone::ItemZone() {}

Item* ItemZone::operator[](int x) {
	int i = 0;
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (i == x) {
			return it->second.item;
		}
	}
	return NULL;
}

ItemZone::KeysItem* ItemZone::getItem(char symbol) {
	auto result = contents.find(symbol);
	if (result != contents.end()) {
		return &result->second;
	}
	return NULL;
}

ItemZone::KeysItem* ItemZone::getItem(Item& item) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.item == &item) {
			return &(it->second);
		}
	}
	return NULL;
}

void ItemZone::add(Item& item) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.item->getType() == item.getType()) {
			it->second.quantity += 1;
			delete &item;
		}
	}
	if (contents.size() >= MAX_SIZE) {
		return;
	}
	char key = getFreeChar();
	if (key == '0') {
		return;
	}
	contents.insert(std::make_pair(key, ItemZone::KeysItem(&item, 1)));
}

char ItemZone::getFreeChar() {
	for (char c : KEYS) {
		for (auto it=contents.begin(); it != contents.end(); it++) {
			if (it->first == c) {
				goto L_Outer;
			}
		}
		return c;
		L_Outer:;
	}
	return '0';
}

bool ItemZone::contains(Item* item) {
	return getItem(*item) != NULL;
}

bool ItemZone::contains(const std::string& itemName) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.item->getName() == itemName) {
			return true;
		}
	}
	return false;
}

std::map<char, ItemZone::KeysItem>& ItemZone::getContents() {
	return contents;
}

bool ItemZone::remove(Item* item) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.item == item) {
			it->second.quantity -= 1;
			if (it->second.quantity <= 0) {
				contents.erase(it);
			}
			return true;
		}
	}
	return false;
}