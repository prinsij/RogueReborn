/**
 * @file random.h
 * @author Team Rogue++
 * @date December 02, 2016
 *
 * @brief Member declarations for the Generator class
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
		/** Random percent from 0 to 100 */
		static int randPercent();
		/** Random coord in box deliniated by topleft,
		 *  bottomright.
		 */
		static Coord randPosition(Coord, Coord);
		/** Rolls the designated dice and returns sum. */
		static int nDx(int numDice, int numFaces);
	private:
		/** std lib generator (m-twister). */
		static std::mt19937 gen;
};
