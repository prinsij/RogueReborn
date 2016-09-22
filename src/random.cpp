#include <random>
#include "include/random.h"

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
