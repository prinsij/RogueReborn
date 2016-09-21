
#ifndef COORD_H
#define COORD_H

class Coord {
	public:
		int& operator[](int);
		Coord operator+(Coord);
		Coord operator-(Coord);

	private:
		int x;
		int y;
};

#endif
