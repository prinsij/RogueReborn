#include "item.h"
#include <vector>

class ItemZone {
	public:
		Item operator[](int);
		bool remove(Item);
		void add(Item);
	private:
		std::vector<Item> contents;
}

