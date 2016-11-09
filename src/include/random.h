/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: random.h
 */ 

#pragma once

#include <random>
#include <string>
#include <vector>

#include "coord.h"

/** Light wrapper around the std library
 *  which provides various random generation
 *  utilities.
 */
class Generator {
	public:
		/** Random integer from range (inclusive). */
		static int intFromRange(int, int);
		/** Random double between 0 and 1 (inclusive). */
		static double rand();
		/** Random boolean. */
		static bool randBool();
		/** Random coord in box deliniated by topleft,
		 *  bottomright.
		 */
		static Coord randPosition(Coord, Coord);
		/** Randomly shuffle the vector provided */
		template<typename T>
		static void shuffle(std::vector<T>*);
	private:
		/** std lib generator (m-twister). */
		static std::mt19937 gen;
};
