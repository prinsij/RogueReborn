/**
 * @file test.testable.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.testable.h"

void Testable::assert(bool condition, std::string comment) {
	if (condition && !onlyShowFailures){
		std::cout << "TESTER 0 Test " << std::to_string(++count) << " success: " << comment << std::endl;
	} else {
		std::cout << "TESTER 1 Test " << std::to_string(++count) << " FAILURE: " << comment << std::endl;
	}
}

void Testable::comment(std::string comment){
	if (!onlyShowFailures){
		std::cout << "TESTER # " << comment << std::endl;
	}
}

Testable::~Testable(){}