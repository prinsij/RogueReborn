
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
		Coord asScreen();
		Coord copy();
	private:
		int x, y;
		static const int MAPX = 0, MAPY = 0;
};

#endif
