/**
 * @file random.cpp
 * @author Team Rogue++
 * @date December 07, 2016
 *
 * @brief Global members
 */ 

#include <algorithm>
#include <random>

#include "include/coord.h"
#include "include/random.h"


//inclusive
int Generator::intFromRange(int lower, int upper) {
	std::cout << lower << upper << "\n";
	if (upper <= lower) {
		return lower;
	}
	return std::uniform_int_distribution<>(lower, upper)(gen);
}

double Generator::rand() {
	return std::uniform_real_distribution<>(0, 1)(gen);
}

bool Generator::randBool() {
	return rand() < 0.5;
}

int Generator::randPercent() {
	return std::uniform_int_distribution<>(0, 100)(gen);
}

Coord Generator::randPosition(Coord a, Coord b) {
	int minX = std::min(a[0], b[0]);
	int maxX = std::max(a[0], b[0]);
	int minY = std::min(a[1], b[1]);
	int maxY = std::max(a[1], b[1]);

	return Coord(intFromRange(minX, maxX), intFromRange(minY, maxY));
}

int Generator::nDx(int numDice, int numFaces) {
	int sum = 0;
	for (auto i=0; i < numDice; i++) {
		sum += intFromRange(1, numFaces);
	}
	return sum;
}
