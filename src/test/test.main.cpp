#ifndef MAIN_TEST
#define MAIN_TEST

#include <string>
#include <vector>
#include <iostream>

#include "test.armor.cpp"
#include "test.testable.cpp"


int main(){

	ArmorTest a = ArmorTest();

	bool b = a.test();

	if (b){
		std::cout << "Done!" << std::endl;
	}

	return 0;

}

#endif