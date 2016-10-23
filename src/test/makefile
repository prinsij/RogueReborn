
source: *.cpp
	@echo Compiling tests...
	@g++ -g *.cpp -o TestRogueReborn.exe -L. -I../libtcod/include -Wl,-rpath=. -Wall -std=c++11

clean:
	@rm -f TestRogueReborn.exe

default: source