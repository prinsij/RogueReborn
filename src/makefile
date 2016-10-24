source: *.cpp

	#Setting up...

	@cp ./libtcod/*.so .

	@rm -rf temp/
	@mkdir temp
	@cp *.cpp temp/

	@bash .hiddenmv

	@cp test/*.cpp .

	#Compiling...
	@g++ -g -c *.cpp -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	#Linking source...
	@g++ -g -o RogueReborn.exe zz.*.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@rm -f zz.main.o

	#Linking tests...
	@g++ -g -o Test.exe *.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	#Cleaning up...
	@rm -f *.o *.cpp
	@cp temp/*.cpp .

recall:
	@bash .recall

clean:
	@rm -f *.exe *.so *.o
	@rm -f scores.txt

default: source