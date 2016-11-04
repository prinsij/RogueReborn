/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: coord.h
 */ 

#pragma once

#include <string>

class Coord {
	public:
		Coord(int, int);
		Coord();
		int& operator[](int);
		Coord operator+(const Coord&);
		Coord operator-(const Coord&);
		Coord operator*(const int&);
		Coord& operator+=(const Coord&);
		Coord& operator-=(const Coord&);

		bool operator<(const Coord&) const;

		Coord& operator*=(const int&);
		bool operator==(const Coord&);
		bool operator!=(const Coord&);
		Coord asScreen();
		Coord copy();
		bool isAdjacentTo(const Coord&) const;
		std::string toString() const;
		// maximum distance in either dimension
		int distanceTo(const Coord&) const;
		static Coord ORTHO[4];
	private:
		int x, y;
		static const int MAPX = 0, MAPY = 2;
};