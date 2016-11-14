/**
 * @file test.testable.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <string>

class Testable {
	public:
		virtual void test() = 0;

		void assert(bool condition, std::string comment) {
			if (condition && !onlyShowFailures){
				std::cout << "TESTER 0 Test " << std::to_string(++count) << " success: " << comment << std::endl;
			} else {
				std::cout << "TESTER 1 Test " << std::to_string(++count) << " FAILURE: " << comment << std::endl;
			}
		}

		void comment(std::string comment){
			if (!onlyShowFailures){
				std::cout << "TESTER # " << comment << std::endl;
			}
		}

	private:
		int count = 0;
		bool onlyShowFailures = false;
};