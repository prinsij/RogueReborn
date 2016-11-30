/**
 * @file test.testable.cpp
 * @author Team Rogue++
 * @date November 29, 2016
 *
 * @brief Global members
 */ 

#include <iostream>
#include <string>
#include <vector>

#include "test.testable.h"

void Testable::assert(bool condition, std::string comment) {
	if (!condition){
		std::cout << "TESTER 1 Test " << std::to_string(++count) << " FAILURE: " << comment << std::endl;
	} else if (!onlyShowFailures) {
		std::cout << "TESTER 0 Test " << std::to_string(++count) << " success: " << comment << std::endl;
	}
}

void Testable::comment(std::string comment){
	if (!onlyShowFailures){
		std::cout << "TESTER # " << comment << std::endl;
	}
}

void Testable::test() {
	std::cout << "TESTER # Test is not implemented yet." << std::endl;
}
Testable::~Testable(){}
