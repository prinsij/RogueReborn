#include <string>
#include <vector>
#include <iostream>

#include "include/armor.h"

int test(){

	Armor a = Armor(Coord(5,5));

	std::cout << a.getRating() << std::endl;

	return 0;
}