/**
 * @file test.testable.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Member declarations for the Testable class
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

class Testable {
	public:
		virtual void test() = 0;
		virtual ~Testable();

		void assert(bool condition, std::string comment);

		void comment(std::string comment);

	private:
		int count = 0;
		bool onlyShowFailures = false;
};