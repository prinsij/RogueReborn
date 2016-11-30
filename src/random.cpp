/**
 * @file random.cpp
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#include <algorithm>
#include <random>

#include "include/coord.h"
#include "include/random.h"

std::mt19937 Generator::gen = std::mt19937(std::random_device()());

//inclusive
int Generator::intFromRange(int lower, int upper) {
	return std::uniform_int_distribution<>(lower, upper)(gen);
}

double Generator::rand() {
	return std::uniform_real_distribution<>(0, 1)(gen);
}

bool Generator::randBool() {
	return rand() < 0.5;
}

Coord Generator::randPosition(Coord a, Coord b) {
	return Coord(intFromRange(a[0], b[0]), intFromRange(a[1], b[1]));
}

template<typename T>
void Generator::shuffle(std::vector<T>* s) {
	std::random_shuffle(s->begin(), s->end());
}

int Generator::nDx(int numDice, int numFaces) {
	int sum = 0;
	for (auto i=0; i < numDice; i++) {
		sum += intFromRange(1, numFaces);
	}
	return sum;
}
