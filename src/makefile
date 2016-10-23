source: *.cpp
	@echo Compiling sources...
	@cp ./libtcod/*.so .
	@g++ -g *.cpp -o RogueReborn.exe -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11
	@make source -C test

tests:
	@make source -C test

runtest:
	@./test/TestRogueReborn.exe

clean:
	@rm -f RogueReborn.exe *.so
	@rm -f scores.txt
	@make clean -C test

default: source