all: src/*.cpp
	g++ src/*.cpp -o RogueReborn.exe -I./src/tcodsrc -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

clean:
	rm RogueReborn.exe
