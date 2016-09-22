
#ifndef COORD_H
#define COORD_H

class Coord {
	public:
		Coord(int, int);
		int& operator[](int);
		Coord operator+(const Coord&);
		Coord operator-(const Coord&);

	private:
		int x;
		int y;
};

#endif
