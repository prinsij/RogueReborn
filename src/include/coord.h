class Coord {
	public:
		int& operator[](int);
		Coord operator+(Coord, Coord);
		Coord operator-(Coord, Coord);

	private:
		int x, int y;
}
