#ifndef MAIN_TEST
#define MAIN_TEST

#include <string>
#include <vector>
#include <iostream>

#include "armor.test.cpp"
#include "testable.test.cpp"


int main(){

	ArmorTest a = ArmorTest();

	bool b = a.test();

	return 0;

}

#endif