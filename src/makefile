all: *.cpp
	@cp ./libtcod/*.so .
	@g++ *.cpp -o RogueReborn.exe -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

clean:
	@rm RogueReborn.exe *.so
