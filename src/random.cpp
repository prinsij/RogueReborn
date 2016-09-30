#include <random>
#include "include/random.h"
#include "include/coord.h"

Generator::Generator() {
	gen = std::mt19937(std::random_device()());
}

//inclusive
int Generator::intFromRange(int lower, int upper) {
	return std::uniform_int_distribution<>(lower, upper)(gen);
}

double Generator::operator()() {
	return std::uniform_real_distribution<>(0, 1)(gen);
}

Coord Generator::randPosition(Coord a, Coord b) {
	return Coord(intFromRange(a[0], b[0]), intFromRange(a[1], b[1]));
}