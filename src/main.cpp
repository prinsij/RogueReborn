#include <iostream>
#include <vector>

using namespace std;

void printMap(vector<vector<char>> map) {

	cout << "+-";

	for (int i = 0; i < map.size(); i++){
		cout << "--";
	}

	cout << '+' << endl;;

	for (vector<char> i : map) {

		cout << '|';

		for (char j : i){
			cout << ' ' << j;
		}

		cout << " |" << endl;
	}

	cout << "+-";

	for (int i = 0; i < map.size(); i++){
		cout << "--";
	}

	cout << '+' << endl;
}

vector<vector<char>> getMap(int playerX, int playerY, int mapSize){

	vector<vector<char>> map(mapSize);

	for (int i = 0; i < map.size(); i++){
		map[i] = vector<char>(mapSize);
	}

	int k = 0;
	for (vector<char>& i : map) {
		for (char& j : i){
			j = ' ';
		}
	}

	map[playerY][playerX] = '#';

	return map;
}

int main() {

	cout << "Welcome to RogueReborn" << endl;

	printMap(getMap(5,5,10));
}