all: *.cpp
	@cp ./libtcod/*.so .
	@g++ -g *.cpp -o RogueReborn.exe -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

default: all

clean:
	@rm -f RogueReborn.exe *.so
	@rm -f scores.txt
