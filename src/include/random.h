#include <random>

#ifndef RANDOM_H
#define RANDOM_H

class Generator {
	public:
		Generator();
		int getNum(int, int);
	private:
		std::mt19937 gen;
}

#endif
