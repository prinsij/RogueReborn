#include <string>
#include <vector>
#include <iostream>

#include "../include/armor.h"
#include "../armor.cpp"

#include "../include/coord.h"
#include "../coord.cpp"

#include "../include/item.h"
#include "../item.cpp"

#include "../include/feature.h"
#include "../feature.cpp"

int main(){

	Armor a = Armor(Coord(5,5));

	std::cout << a.getRating() << std::endl;

	return 0;
}