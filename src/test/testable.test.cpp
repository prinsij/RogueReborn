#ifndef TESTABLE
#define TESTABLE

#include <string>
#include <vector>
#include <iostream>

class Testable {
	public:
		virtual bool test() = 0;
};

#endif