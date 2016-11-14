/**
 * @file test.testable.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Testable class
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

class Testable {
	public:
		virtual void test() = 0;

		void assert(bool condition, std::string comment);

		void comment(std::string comment);

	private:
		int count = 0;
		bool onlyShowFailures = false;
};
