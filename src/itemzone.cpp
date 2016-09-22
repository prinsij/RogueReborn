
#include <string>
#include <iostream>
#include <vector>

#include "include/itemzone.h"
#include "include/item.h"

void ItemZone::add(Item toAdd) {
	contents.push_back(toAdd);
}

bool ItemZone::remove(Item toRemove) {
	int* removeIndex = nullptr;
	*removeIndex = -1;
	for (uint i = 0; i < contents.size(); i++){
		if (contents[i] == toRemove){
			*removeIndex = i;
		}
	}

//	if (*removeIndex == -1) return false;
//	else {
//		contents.erase(removeIndex);
//		return true;
//	}
	contents.erase(&toRemove);
}

