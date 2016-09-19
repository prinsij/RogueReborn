class Terrain {
	public:
		static enum Passability {Blocked, Passable};
		static enum Visibility {Blocked, Corridor, Transparent};
		char getChar();
		Passability isPassable();
		Visibility getVisibility();
	private:
		char character;
		Visibility visible;
		Passability passable;
}
