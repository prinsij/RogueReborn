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

void Generator::shuffle(std::vector<Coord>* s) {
	std::random_shuffle(s->begin(), s->end());
}
