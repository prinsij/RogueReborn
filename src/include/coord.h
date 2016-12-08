/**
 * @file coord.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the Coord class
 */ 

#pragma once

#include <string>

/** Represents a location within the dungeon
 *  or on the screen.
 */
class Coord {
	public:
		/** (x,y) constructor. */
		Coord(int, int);
		/** (0,0) constructor. */
		Coord();
		/** Access param dimension magnitude. */
		int& operator[](int);
		/** Add two coords together. */
		Coord operator+(const Coord&);
		/** Subtract two coords. */
		Coord operator-(const Coord&);
		/** Multiply all vector items by scalar. */
		Coord operator*(const int&);
		/** Augmented assignment for addition. */
		Coord& operator+=(const Coord&);
		/** Augmented assignment for subtraction. */
		Coord& operator-=(const Coord&);

		/** Order coords by overall magnitude. */
		bool operator<(const Coord&) const;

		/** Multiply two coords (item by item). */
		Coord& operator*=(const int&);
		/** True if all vector items equal. */
		bool operator==(const Coord&);
		/** Inverse of == operator. */
		bool operator!=(const Coord&);
		/** Convert position in level to position in screen. */
		Coord asScreen();
		/** Return a copy of this coord. */
		Coord copy();
		/** Return distance(taxicab) <= 1. */
		bool isAdjacentTo(const Coord&) const;
		/** Format as x, y. */
		std::string toString() const;
		/** Maximum distance in either dimension */
		int distanceTo(const Coord&, bool taxicab=true) const;
		/** Set of unit vectors. */
		static Coord ORTHO[4];
	private:
		/** Magnitude in each dimension. */
		int x, y;
		/** Offset of screen vs level. */
		static const int MAPX = 0, MAPY = 2;
};
