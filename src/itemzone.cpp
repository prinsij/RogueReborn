/**
 * @file itemzone.cpp
 * @author Team Rogue++
 * @date November 14, 2016
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
		for (auto item : it->second) {
			if (i == x) {
				return item;
			}
			++i;
		}
	}
	return NULL;
}

std::vector<Item*>* ItemZone::getItem(char symbol) {
	auto result = contents.find(symbol);
	if (result != contents.end()) {
		return &result->second;
	}
	return NULL;
}

std::vector<Item*>* ItemZone::getItem(Item& item) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		for (auto i : it->second) {
			if (*i == item) {
				return &it->second;
			}
		}
	}
	return NULL;
}

bool ItemZone::add(Item& item) {
	if (getCurrWeight() + item.getWeight() > MAX_WEIGHT) {
		return false;
	}
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.front()->getName() == item.getName()) {
			it->second.push_back(&item);
			return true;
		}
	}
	if (contents.size() >= MAX_SIZE) {
		return false;
	}
	char key = getFreeChar();
	if (key == '0') {
		return false;
	}
	contents.insert(std::make_pair(key, std::vector<Item*> {&item}));
	return true;
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
		for (auto i : it->second) {
			if (i->getName() == itemName) {
				return true;
			}
		}
	}
	return false;
}

std::map<char, std::vector<Item*> >& ItemZone::getContents() {
	return contents;
}

bool ItemZone::remove(Item* item) {
	for (auto it=contents.begin(); it != contents.end(); it++) {
		if (it->second.front()->getName() == item->getName()) {
			for (auto it2=it->second.begin(); it2 != it->second.end(); it2++) {
				if (*it2 == item) {
					it->second.erase(it2);
					if (it->second.size() == 0) {
						contents.erase(it);
					}
					return true;
				}
			}
		}
	}
	return false;
}

int ItemZone::getSize() {
	return contents.size();
}

int ItemZone::getCurrWeight() {
	int sum = 0;
	for (auto it=contents.begin(); it != contents.end(); it++) {
		sum += it->second.front()->getWeight() * it->second.size();
	}
	return sum;
}
