#include <random>

#ifndef RANDOM_H
#define RANDOM_H

class Generator {
	public:
		Generator();
		int intFromRange(int, int);
		double operator()();
	private:
		std::mt19937 gen;
};

#endif
