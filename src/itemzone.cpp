#include "include/itemzone.h"
#include <vector>
#include <algorithm>

using namespace std;

ItemZone::ItemZone()
	: contents() {
}

Item ItemZone::operator[](int i) {
	return contents[i];
}

bool ItemZone::remove(Item& item) {
	auto it = find(begin(contents), end(contents), item);
	if (it != end(contents)) {
		contents.erase(it);
		return true;
	}
	return false;
}

void ItemZone::add(Item& item) {
	contents.push_back(item);
}

bool ItemZone::contains(Item& item) {
	return find(begin(contents), end(contents), item) != end(contents);
}