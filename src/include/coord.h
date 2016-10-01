
#ifndef COORD_H
#define COORD_H

class Coord {
	public:
		Coord(int, int);
		Coord();
		int& operator[](int);
		Coord operator+(const Coord&);
		Coord operator-(const Coord&);
		Coord& operator+=(const Coord&);
		Coord& operator-=(const Coord&);
		bool operator==(const Coord&);
		bool operator!=(const Coord&);
		Coord copy();
	private:
		int x;
		int y;
};

#endif
