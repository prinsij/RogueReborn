

#ifndef COORD_H
#define COORD_H


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
		std::string toString() const;
	private:
		int x, y;
		static const int MAPX = 0, MAPY = 2;
};

#endif
