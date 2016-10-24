source: *.cpp

	#Compiling...

	@cp ./libtcod/*.so .

	@rm -rf temp/
	@mkdir temp
	@cp *.cpp temp/

	@bash .hiddenmv

	@cp test/*.cpp .

	@g++ -g -c *.cpp -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@g++ -g -o RogueReborn.exe zz.*.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@rm -f zz.main.o

	@g++ -g -o Test.exe *.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@rm -f *.o *.cpp
	@cp temp/*.cpp .

recall:
	@rm -f *.cpp
	@cp temp/*.cpp .
	@rm -rf temp/

clean:
	@rm -f *.exe *.so *.o
	@rm -f scores.txt

default: source