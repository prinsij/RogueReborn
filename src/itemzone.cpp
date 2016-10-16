#include <algorithm>
#include <vector>

#include "include/itemzone.h"

ItemZone::ItemZone() {}

Item ItemZone::operator[](int i) {
	return contents[i];
}

void ItemZone::add(Item& item) {
	contents.push_back(item);
}

bool ItemZone::contains(Item* item) {
	return find(contents.begin(), contents.end(), *item) != contents.end();
}

bool ItemZone::contains(const std::string& itemName) {
	for (auto itemIterator = contents.begin() ; itemIterator != contents.end() ; itemIterator++)	
		if (itemIterator->getName() == itemName)
			return true;

	return false;
}

std::vector<Item*> ItemZone::getContents() {
	std::vector<Item*> contentPointers;
	
	for (auto itemIterator = contents.begin() ; itemIterator != contents.end() ; itemIterator++) {
		contentPointers.push_back(&(*itemIterator));
	}

	return contentPointers;
} 

bool ItemZone::remove(Item* item) {
	for (auto itemIterator = contents.begin() ; itemIterator != contents.end() ; itemIterator++) {
		if (*itemIterator == *item) {
			contents.erase(itemIterator);
			return true;
		}
	}	

	return false;
}
