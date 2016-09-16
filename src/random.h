#include <random>

class Generator {
	public:
		Generator();
		int getNum(int, int);
	private:
		std::mt19937 gen;
}
